//
// Created by parsy_b on 3/6/20.
//

#include <iostream>
#include "Cylinder.h"

float Cylinder::intersects(const Line& line) const {
    auto dp = line.o - cb_;
    auto e = line.d - (line.d * cd_) * cd_;
    float a = e.sqrMagnitude();
    auto f = dp - (dp * cd_) * cd_;
    float b = e * f;
    float c = f.sqrMagnitude() - r_ * r_;

    float delta = b * b - a * c;
    if (delta < EPS)
        return INFINITY;
    float t = (-b - std::sqrt(delta)) / a;
    if (t < EPS)
        return INFINITY;
    auto q = line.o + t * line.d;
    if (cd_ * (q - cb_) <= 0 || cd_ * (q - ct_) >= 0) {
        bool changed = false;
        float dist = intersects_base(line, false);
        if (dist < INFINITY) {
            t = dist;
            changed = true;
        }
        dist = intersects_base(line, true);
        if ((dist < INFINITY && !changed) || dist < t) {
            t = dist;
            changed = true;
        }
        if (!changed)
            return INFINITY;
    }
    return t;

}

Line Cylinder::get_normal(const Point& p) const {
    auto pcb = (p - cb_);
    auto pct = (p - ct_);
    if (pct.sqrMagnitude() - r_ * r_ < EPS && pct * cd_ > EPS)
        return {p, cd_};
    if (pcb.sqrMagnitude() - r_ * r_ < EPS && pcb * cd_ < -EPS)
        return {p, -cd_};

    auto v = p - (cb_ + ((p - cb_) * cd_) * cd_);
    std::cout << v * cd_ << std::endl;
    return {p, v.normalized()};
}

TexPixel Cylinder::get_tex(const Point& p) const {
    return tex_.get_tex(p.x(), p.y());
}

float Cylinder::intersects_base(const Line& line, bool bottom) const {
    const auto& c = bottom ? cb_ : ct_;
    const auto& n = bottom ? -cd_ : cd_;

    Point p0 = line.o - c;
    float denom = n * line.d;
    if (std::fabs(denom) < EPS)
        return INFINITY;

    float dist = (-p0 * n) / denom;
    if (dist < EPS)
        return INFINITY;
    Point p = line.o + dist * line.d;

    if ((p - c).sqrMagnitude() - r_ * r_ > EPS)
        return INFINITY;

    return dist;
}
