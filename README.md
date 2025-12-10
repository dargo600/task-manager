# Task Manager

## Introduction

The goal of this project is:
- provide a uniform calendar to sync schedules
- provide a way to track tasks and how long things take

## Getting Started

### Prerequisites

Using ubuntu 24
```
sudo apt-get install libboost-dev libboost-filesystem-dev libboost-system-dev libboost-log-dev #version 1.83.0
sudo apt-get install pandoc
```

### Installation
```
# Build and run tests
./build.sh all

#Builds lcoverage report
./build.sh report
```

## RoadMap
- [x] Add initial json code
- [X] Add unit testing, create lcov unit tests
- [] Determine Structure of a task 
- [] Store tasks in a database
- []


## References

* [Building Resftul APIS in C++](https://medium.com/@AlexanderObregon/building-restful-apis-with-c-4c8ac63fe8a7)
* [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
