//
// Created by parsy_b on 3/2/20.
//

#include "Plane.h"

double Plane::intersects(const Line& line) const {
    double denom = norm_ * line.d;
    if (std::fabs(denom) > EPS) {
        double dist = ((pos_ - line.o) * norm_) / denom;
        if (dist > EPS)
            return dist;
    }
    return Inf;
}

Line Plane::get_normal(const Point& p) const {
    return {p, norm_};
}

TexPixel Plane::get_tex(const Point& p) const {
    return tex_->get_tex(p.x(), p.y());
}
