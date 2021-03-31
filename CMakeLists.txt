cmake_minimum_required(VERSION 3.5)

project(test)

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
)

target_include_directories(
    test
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

add_executable(
    exp2-1
    src/exp2-1.cpp
)

target_include_directories(
    exp2-1
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

add_executable(
    exp2-2
    src/exp2-2.cpp
)

target_include_directories(
    exp2-2
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

# SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
SET(CMAKE_BUILD_TYPE Debug)
add_compile_options(-O0 -g)