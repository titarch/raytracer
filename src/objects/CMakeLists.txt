add_subdirectory(lights)
add_subdirectory(textures)
add_subdirectory(solids)

add_library(objects INTERFACE)
target_link_libraries(objects INTERFACE lights textures solids)