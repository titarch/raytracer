//
// Created by parsy_b on 3/2/20.
//

#include "Triangle.h"

float Triangle::intersects(const Line& line) const {
    auto h = line.d ^(-e2_);
    auto a = e0_ * h;
    if (std::fabs(a) < EPS) return INFINITY;
    float f = 1.f / a;
    auto s = line.o - v0_;
    float u = f * (s * h);
    if (u < 0.0 || u > 1.0) return INFINITY;
    auto q = s ^e0_;
    float v = f * line.d * q;
    if (v < 0.0 || u + v > 1.0) return INFINITY;
    float t = f * (-e2_ * q);
    if (t < EPS) return INFINITY;

    return t;
}

Line Triangle::get_normal(const Point& p) const {
    return {p, norm_};
}

TexPixel Triangle::get_tex(const Point& p) const {
    return tex_.get_tex(p.x(), p.y());
}
