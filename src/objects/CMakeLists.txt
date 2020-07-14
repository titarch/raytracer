add_subdirectory(lights)
add_subdirectory(textures)
add_subdirectory(solids)

target_include_directories(lights INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(textures INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(solids INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")

add_library(objects INTERFACE)

target_include_directories(objects INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(objects INTERFACE lights textures solids)