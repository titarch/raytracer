set(solids_src_files
        Solid.h
        Intersection.h
        Sphere.h
        Sphere.cpp
        Plane.h
        Plane.cpp
        Triangle.h
        Triangle.cpp)
add_library(solids ${solids_src_files})
target_link_libraries(solids textures)