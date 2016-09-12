#!/bin/sh

find ./ -name CMakeFiles -type d | xargs rm -rf
find \( -name CMakeCache.txt -or -name Makefile -or -name cmake_install.cmake \
                             -or -name install_manifest.txt \) -type f -delete

find ./dem_diff -name "dem_diff*" -type f -delete
find ./height_check_control -name "height_check_control*" -type f -delete
find ./dark_object_subtraction -name "dark_object_subtraction*" -type f -delete

cmake -DCMAKE_BUILD_TYPE=Release .

make install
