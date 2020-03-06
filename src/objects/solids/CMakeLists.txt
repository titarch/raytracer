set(solids_src_files
        Solid.h
        Intersection.h
        Sphere.h
        Sphere.cpp
        Plane.h
        Plane.cpp
        Triangle.h
        Triangle.cpp Cylinder.cpp Cylinder.h MetaTriangle.cpp MetaTriangle.h Wrapper.cpp Wrapper.h)
add_library(solids ${solids_src_files})
target_link_libraries(solids textures)