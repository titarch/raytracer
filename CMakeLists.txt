cmake_minimum_required(VERSION 3.10)
project(raytracer)

set(CMAKE_CXX_STANDARD 20)

set(EXECUTABLE_NAME raytracer)

set(CMAKE_CXX_FLAGS_RELEASE  "-O3 -Wall -Wextra -Werror -pedantic -fopenmp")
set(CMAKE_CXX_FLAGS_DEBUG    "-g -O3 -Wall -Wextra -Werror -pedantic -fopenmp")

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
find_package(OpenMP REQUIRED)
find_package(YAML-CPP REQUIRED)
find_package(Boost COMPONENTS program_options REQUIRED)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

include_directories(${Boost_INCLUDE_DIR})

add_subdirectory(src)

target_include_directories(${EXECUTABLE_NAME} PUBLIC src)

