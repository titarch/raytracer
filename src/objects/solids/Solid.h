//
// Created by parsy_b on 3/2/20.
//

#ifndef RAYTRACER_SOLID_H
#define RAYTRACER_SOLID_H

#include <memory>
#include <vector>
#include "../textures/TexPixel.h"
#include "../textures/TexMat.h"
#include "../../utils/Line.h"

constexpr double EPS = 1e-3;
constexpr double Inf = std::numeric_limits<double>::infinity();

class Solid {
public:
    explicit Solid(Point const& pos, texmat_ptr const& tex) : pos_(pos), tex_(tex) {}

    virtual double intersects(Line const& line) const = 0;
    virtual Line get_normal(Point const& p) const = 0;
    virtual TexPixel get_tex(Point const& p) const = 0;

protected:
    Point pos_;
    texmat_ptr tex_;
};

using solid_ptr = std::unique_ptr<Solid>;
using solids = std::vector<solid_ptr>;

#endif //RAYTRACER_SOLID_H
