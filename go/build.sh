#!/bin/bash
#
build()
{
    go run server.go
}

if [ "$1" == "all" ]; then
    build
    exit 0
else
    echo "Undefined Function: $1"
fi
