add_subdirectory(utils)
add_subdirectory(objects)
add_subdirectory(engine)

add_executable(${EXECUTABLE_NAME} main.cpp)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

target_link_libraries(${EXECUTABLE_NAME} PUBLIC ${Boost_LIBRARIES} Eigen3::Eigen)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE utils objects engine)
