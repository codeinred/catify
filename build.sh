#!/bin/bash

# This gets the current directory of build.sh, then moves into that directory
cd "$(dirname "$0")"

compilers=(
    "clang++-12"
    "clang++"
    "g++-11"
    "g++"
)

for compiler in "${compilers[@]}"; do
    if which "${compiler}" 2> /dev/null; then
        cxx="${compiler}"
        break
    fi
done

# build project in $project_root/build
cmake --preset="default" -DCMAKE_CXX_COMPILER="${cxx}" "${@}"
cmake --build --preset="default"
