#!/bin/bash
#

build()
{
    [ ! -e build ] && mkdir build
    cp -r res build/
    cmake -S . -B build -Wno-dev
    ret=$?
    if [ $ret -ne 0  ]; then
        echo "Initial cmake build failed"
        exit 1
    fi
    cmake --build build
    ret=$?
    if [ $ret -ne 0 ]; then
        echo "Failed to do cmake"
        exit 1
    fi
    (cd build && ctest)
}

report()
{
    mkdir lcov-report
    lcov --capture --directory build/CMakeFiles/runTests.dir --output-file lcov-report/coverage.info
    result=$?
    if [ $result -ne 0  ]; then
        echo -e "\nFIXME: Failed to do lcov result: $result"
    fi
    genhtml lcov-report/coverage.info --output-directory lcov-report
    result=$?
    if [ $result -ne 0  ]; then
        echo -e "\nFIXME: Failed to do genhtml: $result"
    fi
}

clean()
{
    rm -rf build
}

if [ $# -eq 0 ]; then
    echo "Usage: $0 {clean|all|report}"
    exit 1
fi

if [ "$1" == "clean" ]; then
    clean
    exit 0
elif [ "$1" == "all" ]; then
    build
    exit 0
elif [ "$1" == "report" ]; then
    report
    exit 0
else
    echo "Undefined Function: $1"
fi
