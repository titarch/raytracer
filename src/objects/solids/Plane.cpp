//
// Created by parsy_b on 3/2/20.
//

#include "Plane.h"

float Plane::intersects(const Line& line) const {
    float denom = norm_ * line.d;
    if (std::fabs(denom) > EPS) {
        float dist = ((pos_ - line.o) * norm_) / denom;
        if (dist > EPS)
            return dist;
    }
    return INFINITY;
}

Line Plane::get_normal(const Point& p) const {
    return {p, norm_};
}

TexPixel Plane::get_tex(const Point& p) const {
    return tex_.get_tex(p.x(), p.y());
}
