set(textures_src_files
        TexPixel.h
        TexMat.h
        UniTex.h
        UniTex.cpp)
add_library(textures ${textures_src_files})
target_link_libraries(textures utils)
