cmake_minimum_required(VERSION 3.10)
project(raytracer)

set(CMAKE_CXX_STANDARD 20)

set(EXECUTABLE_NAME raytracer)

set(CMAKE_CXX_FLAGS_RELEASE  "-O3 -Wall -Wextra -fopenmp")
set(CMAKE_CXX_FLAGS_DEBUG    "-g -O3 -Wall -Wextra -fopenmp")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(${Boost_INCLUDE_DIR})

add_subdirectory(src)
