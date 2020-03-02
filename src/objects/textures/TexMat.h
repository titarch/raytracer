//
// Created by parsy_b on 3/2/20.
//

#ifndef RAYTRACER_TEXMAT_H
#define RAYTRACER_TEXMAT_H

#include "TexPixel.h"

class TexMat {
public:
    virtual TexPixel get_tex(float x, float y) = 0;
};

#endif //RAYTRACER_TEXMAT_H
