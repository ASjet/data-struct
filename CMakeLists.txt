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

# SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
SET(CMAKE_BUILD_TYPE Debug)
add_compile_options(-O0 -g)