cmake_minimum_required(VERSION 3.10)
project(raytracer)

set(CMAKE_CXX_STANDARD 20)

set(EXECUTABLE_NAME raytracer)

set(CMAKE_CXX_FLAGS_RELEASE  "-O3 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG    "-g  -Wall -Wextra")

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
find_package(OpenMP REQUIRED)
find_package(YAML-CPP REQUIRED)

add_subdirectory(src)

