#!/usr/bin/env bash

# Build application for Linux by cmake

# Check cmake version
#~/cmake-4.0.1-linux-x86_64/bin/cmake --version

# Precomplie iostream module to prevent compilation errors
#g++ -std=c++23 -fmodules-ts -xc++-system-header iostream

SCRIPT_DIR=$(dirname "$(readlink -f $0)")
DEBUG_DIR=${SCRIPT_DIR}/Debug
if [ ! -d ${DEBUG_DIR} ]; then
	mkdir ${DEBUG_DIR}
fi

g++ Src/main.cpp --std=c++23 -fmodules-ts -o ./Debug/goodnight.elf
