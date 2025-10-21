
if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
  cmake_policy(SET CMP0135 NEW)
endif()

find_package(Boost REQUIRED COMPONENTS system filesystem)
include_directories(${Boost_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/src/api)
set(API_SOURCES
"api/handler.cc"
"api/listener.cc"
"api/pandoc_md_parser.cc"
"api/session.cc"
)

add_executable(task-mgr main.cc)
target_sources(task-mgr PRIVATE ${API_SOURCES})
target_link_libraries(task-mgr PUBLIC ${Boost_LIBRARIES} nlohmann_json::nlohmann_json)

target_link_libraries(task-mgr PUBLIC coverage_config)