#!/bin/sh
cmake -G "Unix Makefiles"
make
rm Makefile
rm -rf CMakeFiles
rm CMakeCache.txt
rm cmake_install.cmake
