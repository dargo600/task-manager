#!/bin/bash
#

build()
{
    if [ ! -d build ]; then
        mkdir build
    fi
    cd build
    cp -r ../res .
    cmake ../src
    make
}

clean()
{
    rm -rf build
}

if [ $# -eq 0 ]; then
    echo "Usage: $0 {clean|all}"
    exit 1
fi

if [ "$1" == "clean" ]; then
    clean
    exit 0
elif [ "$1" == "all" ]; then
    build
    exit 0
fi