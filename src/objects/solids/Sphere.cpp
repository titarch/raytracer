//
// Created by parsy_b on 3/2/20.
//

#include "Sphere.h"

double Sphere::intersects(const Line& line) const {
    Vector oc = line.o - pos_;
    double a = line.d.sqrMagnitude();
    double b = 2.0 * line.d * oc;
    double c = oc.sqrMagnitude() - r_ * r_;
    double delta = b * b - 4 * a * c;
    if (delta < 0)
        return Inf;
    double dist = (-b - std::sqrt(delta)) / (2 * a);
    if (dist < EPS)
        return Inf;
    return dist;
}

Line Sphere::get_normal(Point const& p) const {
    return Line{p, (p - pos_).normalized()};
}

TexPixel Sphere::get_tex(Point const& p) const {
    return tex_->get_tex(p.x(), p.y());
}
