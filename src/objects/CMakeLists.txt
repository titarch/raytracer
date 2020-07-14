add_subdirectory(lights)
add_subdirectory(textures)
add_subdirectory(solids)

add_library(objects INTERFACE)

target_include_directories(objects INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(objects INTERFACE lights textures solids)