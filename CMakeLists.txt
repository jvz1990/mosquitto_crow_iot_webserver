cmake_minimum_required(VERSION 3.15)
project(mosquitto_crow_iot_webserver VERSION 1.0 LANGUAGES CXX)

# Use Conan's toolchain file
include(${CMAKE_BINARY_DIR}/build/Release/generators/conan_toolchain.cmake)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find and link Conan dependencies
find_package(fmt REQUIRED)
find_package(Crow REQUIRED)

# Find PkgConfig for Mosquitto (used for mosquittopp)
find_package(PkgConfig REQUIRED)
pkg_check_modules(MOSQUITTO REQUIRED libmosquitto)

# Add source files
set(SOURCES
    src/main.cpp
    src/MQTTClient.cpp
)

# Include directories for header files
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${MOSQUITTO_INCLUDE_DIRS}
)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link against libraries
target_link_libraries(${PROJECT_NAME}
    fmt::fmt
    Crow::Crow
    ${MOSQUITTO_LIBRARIES}
    mosquittopp
)
