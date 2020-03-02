add_subdirectory(utils)
add_subdirectory(objects)
add_subdirectory(engine)

add_executable(${EXECUTABLE_NAME} main.cpp)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE utils objects engine)
