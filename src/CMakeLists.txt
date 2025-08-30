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

find_package(Boost REQUIRED COMPONENTS system filesystem)
include_directories(${Boost_INCLUDE_DIRS})

set(JSON_SERVER_SOURCES 
"json_server/api_handler.cc"
"json_server/listener.cc"
"json_server/session.cc"
)
add_executable(task-mgr main.cc ${JSON_SERVER_SOURCES})
target_link_libraries(task-mgr ${Boost_LIBRARIES} nlohmann_json::nlohmann_json)
