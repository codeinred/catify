#!/bin/bash

# This gets the current directory of build.sh, then moves into that directory
cd "$(dirname "$0")"

if which g++-11 2> /dev/null; then
    compiler="g++-11"
else
    compiler="g++"
fi

# build project in $project_root/build
cmake --preset="default" -DCMAKE_CXX_COMPILER="${compiler}" "${@}"
cmake --build --preset="default"
