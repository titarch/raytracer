cmake_minimum_required(VERSION 3.16)
project(raytracer)

set(CMAKE_CXX_STANDARD 20)

add_executable(raytracer main.cpp Point.cpp Point.h Color.cpp Color.h Vector.cpp Vector.h Image.cpp Image.h Scene.cpp Scene.h Textures.cpp Textures.h objects.cpp objects.h lights.cpp lights.h Camera.cpp Camera.h)