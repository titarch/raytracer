//
// Created by parsy_b on 3/2/20.
//

#include "Sphere.h"

float Sphere::intersects(const Line& line) const {
    Vector oc = line.o - pos_;
    float a = line.d.sqrMagnitude();
    float b = 2.0 * line.d * oc;
    float c = oc.sqrMagnitude() - r_ * r_;
    float delta = b * b - 4 * a * c;
    if (delta < 0)
        return INFINITY;
    float dist = (-b - std::sqrt(delta)) / (2 * a);
    if (dist < EPS)
        return INFINITY;
    return dist;
}

Line Sphere::get_normal(Point const& p) const {
    return Line{p, (p - pos_).normalized()};
}

TexPixel Sphere::get_tex(Point const& p) const {
    return tex_.get_tex(p.x(), p.y());
}
