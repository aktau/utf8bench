#!/bin/bash

set -e
set -u

arg=
if [ "$#" -ne 0 ]; then
    arg="1"
fi

function run() {
    make clean > /dev/null
    make debug
    ./bench $arg
    make clean > /dev/null
    make release
    ./bench $arg
}

export CC=gcc-4.9 && run
export CC=clang-3.4 && run
