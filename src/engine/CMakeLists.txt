set(engine_src_files
        Image.h
        Image.cpp
        Camera.h
        Camera.cpp
        cubetrig.h
        Blob.h
        Blob.cpp
        Scene.h
        Scene.cpp ray.h convert.h)
add_library(engine ${engine_src_files})
target_link_libraries(engine PUBLIC objects utils ${CONAN_LIBS})
