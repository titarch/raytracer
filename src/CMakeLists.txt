add_subdirectory(utils)
add_subdirectory(objects)
add_subdirectory(engine)

add_executable(${EXECUTABLE_NAME} main.cpp)

target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

target_link_libraries(${EXECUTABLE_NAME} PUBLIC ${Boost_LIBRARIES} Eigen3::Eigen)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE utils objects engine)
