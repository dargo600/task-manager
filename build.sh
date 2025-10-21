#!/bin/bash
#

build()
{
    [ ! -e build/tests ] && mkdir -p build/tests
    cp -r res build/tests/
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
    (cd build && ctest --output-on-failure)
}

report()
{
    [ ! -e lcov-report ] && mkdir lcov-report
    lcov --ignore-errors mismatch --capture --directory build/tests/CMakeFiles --output-file lcov-report/coverage.info
    result=$?
    if [ $result -ne 0  ]; then
        echo -e "\nFIXME: Failed to do lcov result: $result"
        exit 1
    fi
    echo "Removing coverage for unwanted directories"
    lcov --ignore-errors unused --remove lcov-report/coverage.info 'gmock*' 'nlohmann*' '/usr/*' '*/googletest/*' '*/test/*' '*/tests/*' '*/external/*' --output-file lcov-report/coverage.info
    result=$?
    if [ $result -ne 0  ]; then
        echo -e "\nFIXME: Failed to do lcov remove: $result"
        exit 1
    fi
    genhtml lcov-report/coverage.info --ignore-errors source --output-directory lcov-report
    result=$?
    if [ $result -ne 0  ]; then
        echo -e "\nFIXME: Failed to do genhtml: $result"
        exit 1
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
