#!/bin/bash
#
build()
{
    go run server.go
}

coverage()
{
    go test -cover .
    go test -coverprofile=c.out
    go tool cover -html=c.out
}

if [ "$1" == "all" ]; then
    build
    exit 0
elif [ "$1" == "coverage" ]; then
    coverage
    exit 0
else
    echo "Undefined Function: $1"
fi
