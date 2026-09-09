import sys, os, re

def generate_wrapper(func_name):
    header_path = f"input/{func_name}.h"
    if not os.path.exists(header_path):
        print(f"Error: Could not find {header_path}")
        sys.exit(1)

    with open(header_path, 'r') as f:
        content = f.read()

    # Find the main function signature
    match = re.search(fr"extern void {func_name}\((.*?)\);", content, re.DOTALL)
    if not match:
        print("Could not find function signature!")
        sys.exit(1)

    args = [arg.strip() for arg in match.group(1).split(',')]
    
    inputs = []
    array_outputs = []
    scalar_outputs = []

    for arg in args:
        if "emxArray_real_T *" in arg:
            array_outputs.append(arg.split('*')[1].strip())
        elif "double *" in arg:
            scalar_outputs.append(arg.split('*')[1].strip())
        elif "double " in arg:
            inputs.append(arg.split('double ')[1].strip())

    # Build the C++ wrapper
    cpp = f"""
#include <emscripten/bind.h>
#include <emscripten/val.h>
#include "input/{func_name}.h"
#include "input/{func_name}_emxAPI.h"

using namespace emscripten;

val run_{func_name}({', '.join([f"double {i}" for i in inputs])}) {{
"""
    # Initialize arrays and scalars
    for arr in array_outputs:
        cpp += f"    emxArray_real_T *{arr} = emxCreateND_real_T(1, 0);\n"
    for scl in scalar_outputs:
        cpp += f"    double {scl} = 0;\n"

    # Call MATLAB function
    call_args = inputs + [f"{arr}" for arr in array_outputs] + [f"&{scl}" for scl in scalar_outputs]
    cpp += f"\n    {func_name}({', '.join(call_args)});\n\n"

    # Convert to JS Float64Arrays
    for arr in array_outputs:
        cpp += f"    val {arr}_view = val(typed_memory_view({arr}->size[0] * {arr}->size[1], {arr}->data));\n"
        cpp += f"    val {arr}_js = val::global(\"Float64Array\").new_({arr}_view);\n"
        cpp += f"    emxDestroyArray_real_T({arr});\n"

    # Bundle JS Object
    cpp += "\n    val result = val::object();\n"
    for arr in array_outputs:
        cpp += f"    result.set(\"{arr}\", {arr}_js);\n"
    for scl in scalar_outputs:
        cpp += f"    result.set(\"{scl}\", {scl});\n"

    cpp += """
    return result;
}

EMSCRIPTEN_BINDINGS(my_module) {
"""
    cpp += f"    function(\"{func_name}\", &run_{func_name});\n"
    cpp += "}\n"

    with open("wrapper.cpp", 'w') as f:
        f.write(cpp)
    print(f"Successfully generated wrapper.cpp for {func_name}!")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python autowrap.py <FunctionName>")
    else:
        generate_wrapper(sys.argv[1])