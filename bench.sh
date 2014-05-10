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
    ./utf8bench $arg
    make clean > /dev/null
    make release
    ./utf8bench $arg
}

export CC=gcc-4.9 && run
export CC=clang-3.4 && run
