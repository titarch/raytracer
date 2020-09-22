set(solids_src_files
        Intersection.h

        Solid.h
        Wrapper.h Wrapper.cpp
        Sphere.h Sphere.cpp
        Plane.h Plane.cpp
        Triangle.h Triangle.cpp
        Cylinder.h Cylinder.cpp
        MetaTriangle.h MetaTriangle.cpp
        Box.h Box.cpp)
add_library(solids ${solids_src_files})
target_link_libraries(solids textures)