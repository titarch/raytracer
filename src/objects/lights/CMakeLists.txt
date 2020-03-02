set(lights_src_files
        Light.h
        Light.cpp
        PointLight.h
        PointLight.cpp)
add_library(lights ${lights_src_files})
target_link_libraries(lights utils)
