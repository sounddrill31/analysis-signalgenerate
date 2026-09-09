import sys
import os
import re

# this script is fully llm generated

def parse_argument(arg_str):
    arg = arg_str.strip()
    is_const = "const" in arg
    has_emx = "emxArray" in arg
    
    # Check for fixed-size array notation e.g., double x[945176]
    array_match = re.search(r'\[\s*(\d+)\s*\]', arg)
    
    if has_emx:
        names = re.findall(r'\b[a-zA-Z_][a-zA-Z0-9_]*\b', arg)
        name = names[-1]
        return {'type': 'array_in_emx' if is_const else 'array_out_emx', 'name': name}
            
    elif array_match:
        size = int(array_match.group(1))
        before_bracket = arg.split('[')[0]
        names = re.findall(r'\b[a-zA-Z_][a-zA-Z0-9_]*\b', before_bracket)
        name = names[-1]
        return {'type': 'array_in_fixed' if is_const else 'array_out_fixed', 'name': name, 'size': size}
            
    elif is_const and "*" in arg:
        names = re.findall(r'\b[a-zA-Z_][a-zA-Z0-9_]*\b', arg)
        name = names[-1]
        return {'type': 'array_in_fixed', 'name': name, 'size': None}
        
    elif "*" in arg:
        names = re.findall(r'\b[a-zA-Z_][a-zA-Z0-9_]*\b', arg)
        name = names[-1]
        return {'type': 'scalar_out', 'name': name}
        
    else:
        names = re.findall(r'\b[a-zA-Z_][a-zA-Z0-9_]*\b', arg)
        name = names[-1]
        return {'type': 'scalar_in', 'name': name}

def generate_wrapper(func_name):
    header_path = f"input/{func_name}.h"
    if not os.path.exists(header_path):
        print(f"Error: Could not find {header_path}")
        sys.exit(1)

    with open(header_path, 'r') as f:
        content = f.read()

    # Find the main function signature
    match = re.search(fr"extern\s+void\s+{func_name}\s*\((.*?)\);", content, re.DOTALL)
    if not match:
        match = re.search(fr"void\s+{func_name}\s*\((.*?)\);", content, re.DOTALL)
    if not match:
        print(f"Error: Could not find function signature for {func_name} in {header_path}!")
        sys.exit(1)

    args_str = match.group(1)
    args = [a.strip() for a in args_str.split(',') if a.strip()]
    parsed_args = [parse_argument(arg) for arg in args]

    inputs = [p for p in parsed_args if p['type'] in ('scalar_in', 'array_in_fixed', 'array_in_emx')]
    outputs = [p for p in parsed_args if p['type'] in ('scalar_out', 'array_out_fixed', 'array_out_emx')]

    # Function signature parameters for C++ wrapper
    cpp_params = []
    for p in inputs:
        if p['type'] == 'scalar_in':
            cpp_params.append(f"double {p['name']}")
        else:
            cpp_params.append(f"const val &{p['name']}_js")

    cpp = f"""#include <emscripten/bind.h>
#include <emscripten/val.h>
#include <vector>
#include <algorithm>
#include "{header_path}"
"""
    # Include helper emx headers if present
    for h in [f"input/{func_name}_emxAPI.h", f"input/{func_name}_emxutil.h", "input/rtwtypes.h"]:
        if os.path.exists(h):
            cpp += f'#include "{h}"\n'

    cpp += f"""
using namespace emscripten;

val run_{func_name}({', '.join(cpp_params)}) {{
"""
    call_args = []
    emx_destroys = []

    # Prepare inputs & outputs
    for p in parsed_args:
        name = p['name']
        p_type = p['type']

        if p_type == 'scalar_in':
            call_args.append(name)

        elif p_type == 'array_in_fixed':
            size = p.get('size')
            size_expr = f"(size_t){size}" if size else f"{name}_len"
            cpp += f"    size_t {name}_len = {name}_js[\"length\"].as<size_t>();\n"
            cpp += f"    std::vector<double> {name}_buf(std::max({size_expr}, {name}_len));\n"
            cpp += f"    if ({name}_len > 0) {{\n"
            cpp += f"        val {name}_view = val(typed_memory_view({name}_len, {name}_buf.data()));\n"
            cpp += f"        {name}_view.call<void>(\"set\", {name}_js);\n"
            cpp += f"    }}\n"
            call_args.append(f"{name}_buf.data()")

        elif p_type == 'array_in_emx':
            cpp += f"    size_t {name}_len = {name}_js[\"length\"].as<size_t>();\n"
            cpp += f"    int {name}_sz = (int){name}_len;\n"
            cpp += f"    emxArray_real_T *{name} = emxCreateND_real_T(1, &{name}_sz);\n"
            cpp += f"    if ({name}_len > 0) {{\n"
            cpp += f"        val {name}_view = val(typed_memory_view({name}_len, {name}->data));\n"
            cpp += f"        {name}_view.call<void>(\"set\", {name}_js);\n"
            cpp += f"    }}\n"
            call_args.append(name)
            emx_destroys.append(f"    emxDestroyArray_real_T({name});\n")

        elif p_type == 'scalar_out':
            cpp += f"    double {name} = 0;\n"
            call_args.append(f"&{name}")

        elif p_type == 'array_out_fixed':
            size = p['size']
            cpp += f"    std::vector<double> {name}_buf({size});\n"
            call_args.append(f"{name}_buf.data()")

        elif p_type == 'array_out_emx':
            cpp += f"    emxArray_real_T *{name} = emxCreateND_real_T(1, 0);\n"
            call_args.append(name)
            emx_destroys.append(f"    emxDestroyArray_real_T({name});\n")

    # MATLAB C call
    cpp += f"\n    {func_name}({', '.join(call_args)});\n\n"

    # Bundle JS result object
    cpp += "    val result = val::object();\n"
    for p in outputs:
        name = p['name']
        p_type = p['type']

        if p_type == 'scalar_out':
            cpp += f"    result.set(\"{name}\", {name});\n"

        elif p_type == 'array_out_fixed':
            size = p['size']
            cpp += f"    val {name}_view = val(typed_memory_view({size}, {name}_buf.data()));\n"
            cpp += f"    val {name}_js = val::global(\"Float64Array\").new_({name}_view);\n"
            cpp += f"    result.set(\"{name}\", {name}_js);\n"

        elif p_type == 'array_out_emx':
            cpp += f"    val {name}_view = val(typed_memory_view({name}->size[0] * {name}->size[1], {name}->data));\n"
            cpp += f"    val {name}_js = val::global(\"Float64Array\").new_({name}_view);\n"
            cpp += f"    result.set(\"{name}\", {name}_js);\n"

    for d in emx_destroys:
        cpp += d

    cpp += "\n    return result;\n}\n\n"

    # Emscripten binding
    cpp += f"EMSCRIPTEN_BINDINGS(my_module) {{\n"
    cpp += f"    function(\"{func_name}\", &run_{func_name});\n"
    cpp += "}\n"

    with open("wrapper.cpp", 'w') as f:
        f.write(cpp)
    print(f"Successfully generated wrapper.cpp for {func_name}!")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python autowrap.py <FunctionName>")
    else:
        generate_wrapper(sys.argv[1].strip())