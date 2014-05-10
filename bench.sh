#!/bin/bash

set -e
set -u

function run() {
    make clean > /dev/null
    make debug
    ./bench
    make clean > /dev/null
    make release
    ./bench
}

export CC=gcc-4.9 && run
export CC=clang-3.4 && run
