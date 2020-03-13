//
// Created by parsy_b on 3/2/20.
//

#ifndef RAYTRACER_SOLID_H
#define RAYTRACER_SOLID_H

#include "../textures/TexPixel.h"
#include "../textures/TexMat.h"
#include "../../utils/Line.h"

constexpr double EPS = 1e-3;
constexpr double Inf = std::numeric_limits<double>::infinity();

class Solid {
public:
    explicit Solid(Point const& pos, TexMat& tex) : pos_(pos), tex_(tex) {}

    virtual double intersects(Line const& line) const = 0;
    virtual Line get_normal(Point const& p) const = 0;
    virtual TexPixel get_tex(Point const& p) const = 0;

protected:
    Point pos_;
    TexMat& tex_;
};

#endif //RAYTRACER_SOLID_H
