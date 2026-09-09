import sys
import os
import re

# This script is completely LLM generated

def parse_argument(arg_str):
    arg = arg_str.strip()
    names = re.findall(r'\b[a-zA-Z_][a-zA-Z0-9_]*\b', arg)
    if not names: return None
    name = names[-1]
    
    # 1. Hardcode inputs so MATLAB keywords can't break them
    if name == 'x':
        return {'type': 'array_in_emx', 'name': name}
    if name == 'Fs':
        return {'type': 'scalar_in', 'name': name}
    
    # 2. Check if MATLAB optimized this output into a fixed-size array (like double freq[513])
    array_match = re.search(r'\[\s*(\d+)\s*\]', arg)
    if array_match:
        size = int(array_match.group(1))
        return {'type': 'array_out_fixed', 'name': name, 'size': size}
        
    # 3. Otherwise, it's a dynamic emxArray output
    return {'type': 'array_out_emx', 'name': name}
    
def generate_wrapper(func_name):
    header_path = f"input/{func_name}.h"
    with open(header_path, 'r') as f:
        content = f.read()

    match = re.search(fr"extern\s+void\s+{func_name}\s*\((.*?)\);", content, re.DOTALL)
    args_str = match.group(1)
    args = [a.strip() for a in args_str.split(',') if a.strip()]
    parsed_args = [parse_argument(arg) for arg in args if arg]

    outputs = [p for p in parsed_args if p['type'] in ('array_out_emx', 'array_out_fixed')]

    cpp = f"""#include <emscripten/bind.h>
#include <emscripten/val.h>
#include <vector>
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
    if (!is_initialized) {{
        {func_name}_initialize();
        is_initialized = true;
    }}
"""
    call_args = []
    emx_destroys = []

    for p in parsed_args:
        name = p['name']
        p_type = p['type']
        
        if name == 'x':
            cpp += f"    size_t x_len = x_js[\"length\"].as<size_t>();\n"
            cpp += f"    int x_sz[2] = {{ 1, (int)x_len }};\n"
            cpp += f"    emxArray_real_T *x = emxCreateND_real_T(2, x_sz);\n"
            cpp += f"    if (x_len > 0) {{\n"
            cpp += f"        val x_view = val(typed_memory_view(x_len, x->data));\n"
            cpp += f"        x_view.call<void>(\"set\", x_js);\n"
            cpp += f"    }}\n"
            call_args.append("x")
            emx_destroys.append("    emxDestroyArray_real_T(x);\n")
        elif name == 'Fs':
            call_args.append("Fs")
        elif p_type == 'array_out_fixed':
            size = p['size']
            cpp += f"    std::vector<double> {name}_buf({size});\n"
            call_args.append(f"{name}_buf.data()")
        else:
            cpp += f"    int {name}_sz[2] = {{ 0, 0 }};\n"
            cpp += f"    emxArray_real_T *{name} = emxCreateND_real_T(2, {name}_sz);\n"
            call_args.append(name)
            emx_destroys.append(f"    emxDestroyArray_real_T({name});\n")

    cpp += f"\n    {func_name}({', '.join(call_args)});\n\n"
    cpp += "    val result = val::object();\n"
    
    for p in outputs:
        name = p['name']
        p_type = p['type']
        if p_type == 'array_out_fixed':
            size = p['size']
            cpp += f"    val {name}_view = val(typed_memory_view({size}, {name}_buf.data()));\n"
            cpp += f"    val {name}_js = val::global(\"Float64Array\").new_({name}_view);\n"
            cpp += f"    result.set(\"{name}\", {name}_js);\n"
        else:
            cpp += f"    int {name}_numels = 1;\n"
            cpp += f"    for (int i = 0; i < {name}->numDimensions; ++i) {name}_numels *= {name}->size[i];\n"
            cpp += f"    val {name}_view = val(typed_memory_view({name}_numels, {name}->data));\n"
            cpp += f"    val {name}_js = val::global(\"Float64Array\").new_({name}_view);\n"
            cpp += f"    result.set(\"{name}\", {name}_js);\n"

    for d in emx_destroys:
        cpp += d

    cpp += "\n    return result;\n}\n\n"
    cpp += f"EMSCRIPTEN_BINDINGS(my_module) {{\n"
    cpp += f"    function(\"{func_name}\", &run_{func_name});\n"
    cpp += "}\n"

    with open("wrapper.cpp", 'w') as f:
        f.write(cpp)
    print(f"Successfully generated BULLETPROOF wrapper.cpp for {func_name}!")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python autowrap.py <FunctionName>")
    else:
        generate_wrapper(sys.argv[1].strip())