//
// Created by parsy_b on 3/2/20.
//

#ifndef RAYTRACER_TEXMAT_H
#define RAYTRACER_TEXMAT_H

#include "TexPixel.h"
#include <memory>
#include <vector>

class TexMat {
public:
    virtual TexPixel get_tex(double x, double y) = 0;
};

using texmat_ptr = std::shared_ptr<TexMat>;
using texmats = std::vector<texmat_ptr>;

#endif //RAYTRACER_TEXMAT_H
