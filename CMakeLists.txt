cmake_minimum_required(VERSION 3.15)
project(cpp_boilerplate VERSION 1.0 LANGUAGES CXX)

# Use Conan's toolchain file
include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add executable
add_executable(${PROJECT_NAME} src/main.cpp)

# Find and link Conan dependencies
find_package(fmt REQUIRED)
target_link_libraries(${PROJECT_NAME} fmt::fmt)
