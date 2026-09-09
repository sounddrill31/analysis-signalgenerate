#!/usr/bin/env bash

# this script is fully llm generated

#fallback to genAnalysisLogic
FUNC_NAME=${1:-genAnalysisLogic}

echo "Generating C++ wrapper for ${FUNC_NAME}..."

# cleanup
rm -rf output
mkdir -p output

python autowrap.py "$FUNC_NAME"

if [ $? -ne 0 ]; then
    echo "❌ Wrapper generation failed!"
    exit 1
fi

echo "Compiling to WebAssembly using emcc..."
emcc input/*.c wrapper.cpp \
    -msimd128 -msse2 \
    -s ALLOW_MEMORY_GROWTH=1 \
    -s INITIAL_MEMORY=33554432 \
    --bind \
    -s MODULARIZE=1 \
    -s EXPORT_NAME="createWasmModule" \
    -I input \
    -I extern/include \
    -o output/index.js

if [ $? -ne 0 ]; then
    echo "❌ Compilation failed!"
    exit 1
fi

echo "Done, index.js and index.wasm generated."