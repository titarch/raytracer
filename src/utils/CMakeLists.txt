set(utils_src_files
        Vector.h
        Matrix.h
        Point.h
        Line.h
        Color.h)
add_library(utils ${utils_src_files})
set_target_properties(utils PROPERTIES LINKER_LANGUAGE CXX)

