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
