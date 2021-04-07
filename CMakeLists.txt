cmake_minimum_required(VERSION 3.5)

project(DataStruct)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
)

add_executable(
    exp2-1
    src/exp2-1.cpp
)

add_executable(
    exp2-2-1
    src/exp2-2-1.cpp
)

add_executable(
    exp2-2-2
    src/exp2-2-2.cpp
)

# SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
SET(CMAKE_BUILD_TYPE Debug)
add_compile_options(-O0 -g)