cmake_minimum_required(VERSION 3.11)
project(TaskManager)
include(FetchContent)

set(CMAKE_CXX_STANDARD 17)

# Avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP in CMake 2.24:
if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
  cmake_policy(SET CMP0135 NEW)
endif()

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)

# GoogleTest
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()



find_package(Boost REQUIRED COMPONENTS system filesystem)
include_directories(${Boost_INCLUDE_DIRS})

set(API_SOURCES 
"api/handler.cc"
"api/listener.cc"
"api/session.cc"
)

add_executable(task-mgr main.cc ${API_SOURCES})
target_link_libraries(task-mgr ${Boost_LIBRARIES} nlohmann_json::nlohmann_json)

#Unit tests
#add_executable(runTests ../tests/api/test_api_handler.cc)
#target_link_libraries(runTests gtest_main gtest ${Boost_LIBRARIES} nlohmann_json::nlohmann_json -lmd4c-html)
#add_test(NAME ApiHandlerTests COMMAND runTests)