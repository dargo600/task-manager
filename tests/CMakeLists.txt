if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
  cmake_policy(SET CMP0135 NEW)
endif()
enable_testing()

cmake_minimum_required(VERSION 3.14)

message(STATUS "Project Source Directory: ${PROJECT_SOURCE_DIR}")

include_directories(${Boost_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/src/api
    ${PROJECT_SOURCE_DIR}/tests/api)

find_package(Boost REQUIRED COMPONENTS system filesystem)
add_executable(tests
    api/test_handler.cc
    ../src/api/handler.cc
    ../src/api/listener.cc
    ../src/api/pandoc_md_parser.cc
    ../src/api/session.cc)
target_link_libraries(
    tests
    PRIVATE
    GTest::gtest_main
    GTest::gmock_main
    ${Boost_LIBRARIES}
    nlohmann_json::nlohmann_json
)
include(GoogleTest)
gtest_discover_tests(tests)
