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
g++ --std=c++23 -fmodules-ts -o ${DEBUG_DIR}/goodnight.elf \
	-Wall -Wextra -Wconversion -Wsign-conversion -Wpedantic \
	${SCRIPT_DIR}/Src/ntp_cl.cppm \
	${SCRIPT_DIR}/Src/powerctl.cppm \
	${SCRIPT_DIR}/Src/correction.cppm \
	${SCRIPT_DIR}/Src/human_time.cppm \
	${SCRIPT_DIR}/Src/goodnight.cpp
