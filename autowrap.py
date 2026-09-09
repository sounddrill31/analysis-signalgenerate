import sys
import os
import re

# This script is completely LLM generated

def parse_argument(arg_str):
    arg = arg_str.strip()
    names = re.findall(r'\b[a-zA-Z_][a-zA-Z0-9_]*\b', arg)
    if not names: return None
    name = names[-1]
    
    has_emx = "emxArray" in arg
    array_match = re.search(r'\[\s*(\d+)\s*\]', arg)
    is_input = (name in ['x', 'Fs'])
    
    if name == 'Fs': return {'type': 'scalar_in', 'name': name}
    if has_emx: return {'type': 'array_in_emx' if is_input else 'array_out_emx', 'name': name}
    if array_match: return {'type': 'array_in_fixed' if is_input else 'array_out_fixed', 'name': name, 'size': int(array_match.group(1))}
    
    # Fallback for plain pointers
    if "*" in arg: return {'type': 'array_in_ptr' if is_input else 'array_out_ptr', 'name': name}
    return {'type': 'scalar_in', 'name': name}

def generate_wrapper(func_name):
    header_path = f"input/{func_name}.h"
    with open(header_path, 'r') as f: content = f.read()

    match = re.search(fr"extern\s+void\s+{func_name}\s*\((.*?)\);", content, re.DOTALL)
    args = [a.strip() for a in match.group(1).split(',') if a.strip()]
    parsed_args = [parse_argument(arg) for arg in args if arg]

    cpp = f"""#include <emscripten/bind.h>
#include <emscripten/val.h>
#include <vector>
#include <algorithm>
#include "{header_path}"
"""
    for h in [f"input/{func_name}_emxAPI.h", f"input/{func_name}_emxutil.h"]:
        if os.path.exists(h): cpp += f'#include "{h}"\n'

    cpp += f"""
using namespace emscripten;

extern "C" {{
    void omp_init_nest_lock(void*) {{}}
    void omp_destroy_nest_lock(void*) {{}}
    void omp_set_nest_lock(void*) {{}}
    void omp_unset_nest_lock(void*) {{}}
    int omp_get_num_threads() {{ return 1; }}
    int omp_get_max_threads() {{ return 1; }}
    int omp_get_thread_num() {{ return 0; }}
    void {func_name}_initialize();
}}

val run_{func_name}(const val &x_js, double Fs) {{
    static bool is_initialized = false;
    if (!is_initialized) {{ {func_name}_initialize(); is_initialized = true; }}
"""
    call_args, emx_destroys = [], []

    for p in parsed_args:
        name, p_type = p['name'], p['type']
        if name == 'Fs':
            call_args.append("Fs")
        elif p_type == 'array_in_emx':
            cpp += f"    size_t x_len = x_js[\"length\"].as<size_t>();\n"
            cpp += f"    int x_sz[2] = {{ 1, (int)x_len }};\n"
            cpp += f"    emxArray_real_T *x = emxCreateND_real_T(2, x_sz);\n"
            cpp += f"    if (x_len > 0) {{\n"
            cpp += f"        val x_view = val(typed_memory_view(x_len, x->data));\n"
            cpp += f"        x_view.call<void>(\"set\", x_js);\n"
            cpp += f"    }}\n"
            call_args.append("x")
            emx_destroys.append("    emxDestroyArray_real_T(x);\n")
        elif p_type in ('array_in_fixed', 'array_in_ptr'):
            size = p.get('size', 944640)
            cpp += f"    std::vector<double> {name}_buf({size}, 0.0);\n"
            cpp += f"    size_t {name}_js_len = x_js[\"length\"].as<size_t>();\n"
            cpp += f"    size_t {name}_copy_len = std::min((size_t){size}, {name}_js_len);\n"
            cpp += f"    if ({name}_copy_len > 0) {{\n"
            cpp += f"        val {name}_view = val(typed_memory_view({name}_copy_len, {name}_buf.data()));\n"
            cpp += f"        {name}_view.call<void>(\"set\", x_js);\n"
            cpp += f"    }}\n"
            call_args.append(f"{name}_buf.data()")
        elif p_type == 'array_out_emx':
            cpp += f"    emxArray_real_T *{name};\n    emxInitArray_real_T(&{name}, 2);\n"
            call_args.append(name)
            emx_destroys.append(f"    emxDestroyArray_real_T({name});\n")
        elif p_type in ('array_out_fixed', 'array_out_ptr'):
            size = p.get('size', 944640)
            cpp += f"    std::vector<double> {name}_buf({size}, 0.0);\n"
            call_args.append(f"{name}_buf.data()")

    cpp += f"\n    {func_name}({', '.join(call_args)});\n    val result = val::object();\n"

    for p in [x for x in parsed_args if 'out' in x['type']]:
        name, p_type = p['name'], p['type']
        if p_type in ('array_out_fixed', 'array_out_ptr'):
            size = p.get('size', 944640)
            cpp += f"    val {name}_view = val(typed_memory_view({size}, {name}_buf.data()));\n"
            cpp += f"    result.set(\"{name}\", val::global(\"Float64Array\").new_({name}_view));\n"
        elif p_type == 'array_out_emx':
            cpp += f"    int {name}_numels = 1;\n"
            cpp += f"    for (int i = 0; i < {name}->numDimensions; ++i) {name}_numels *= {name}->size[i];\n"
            cpp += f"    if ({name}_numels > 0) {{\n"
            cpp += f"        val {name}_view = val(typed_memory_view({name}_numels, {name}->data));\n"
            cpp += f"        result.set(\"{name}\", val::global(\"Float64Array\").new_({name}_view));\n"
            cpp += f"    }} else result.set(\"{name}\", val::global(\"Float64Array\").new_(0));\n"

    for d in emx_destroys: cpp += d
    cpp += "\n    return result;\n}\n\nEMSCRIPTEN_BINDINGS(my_module) {\n"
    cpp += f"    function(\"{func_name}\", &run_{func_name});\n}}\n"

    with open("wrapper.cpp", 'w') as f: f.write(cpp)
    print(f"Successfully generated adaptive wrapper.cpp for {func_name}!")

if __name__ == "__main__":
    if len(sys.argv) < 2: print("Usage: python autowrap.py <FunctionName>")
    else: generate_wrapper(sys.argv[1].strip())