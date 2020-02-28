//
// Created by parsy_b on 2/14/20.
//

#include "objects.h"

float Sphere::intersects(const Line& line) const {
    Vector oc = line.o - pos_;
    float a = line.d.sqrMagnitude();
    float b = 2.0 * line.d * oc;
    float c = oc.sqrMagnitude() - r_ * r_;
    float delta = b * b - 4 * a * c;
    if (delta < 0)
        return -1;
    float dist = (-b - std::sqrt(delta)) / (2 * a);
    if (dist < EPS)
        return -1;
    return dist;
}

Line Sphere::get_normal(Point const& p) const {
    return Line{p, (p - pos_).normalized()};
}

TexPixel Sphere::get_tex(Point const& p) const {
    return tex_.get_tex(p.x(), p.y());
}

float Plane::intersects(const Line& line) const {
    float denom = norm_ * line.d;
    if (std::fabs(denom) > EPS) {
        float dist = ((pos_ - line.o) * norm_) / denom;
        if (dist > EPS)
            return dist;
    }
    return -1;
}

Line Plane::get_normal(const Point& p) const {
    return {p , norm_};
}

TexPixel Plane::get_tex(const Point& p) const {
    return tex_.get_tex(p.x(), p.y());
}
