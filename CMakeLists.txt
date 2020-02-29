cmake_minimum_required(VERSION 3.16)
project(raytracer)

set(CMAKE_CXX_STANDARD 20)

set(EXECUTABLE_NAME raytracer)

set(CMAKE_CXX_FLAGS_RELEASE  "-O3 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG    "-g  -Wall -Wextra")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(${EXECUTABLE_NAME} main.cpp Point.cpp Point.h Color.cpp Color.h Vector.cpp Vector.h Image.cpp Image.h Scene.cpp Scene.h Textures.cpp Textures.h objects.cpp objects.h lights.cpp lights.h Camera.cpp Camera.h Blob.cpp Blob.h cubetrig.h)
target_link_libraries(${EXECUTABLE_NAME} sfml-window sfml-graphics sfml-audio)