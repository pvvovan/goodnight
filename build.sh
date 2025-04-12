#!/usr/bin/env bash

# Build application for Linux by cmake

SCRIPT_DIR=$(dirname "$(readlink -f $0)")
DEBUG_DIR=${SCRIPT_DIR}/Debug

if [ ! -d ${DEBUG_DIR} ]; then
	mkdir ${DEBUG_DIR}
	cd ${DEBUG_DIR}
	# Precomplie iostream module to prevent compilation errors
	g++ -std=c++23 -fmodules-ts -xc++-system-header iostream
fi

cd ${DEBUG_DIR}
g++ ${SCRIPT_DIR}/Src/main.cpp --std=c++23 -fmodules-ts -o ${DEBUG_DIR}/goodnight.elf
