//
// Created by parsy_b on 3/6/20.
//

#include "Cylinder.h"

float Cylinder::intersects(const Line& line) const {
    Point p0 = line.o - cb_;
    float a = line.d.x() * line.d.x() + line.d.z() * line.d.z();
    float b = line.d.x() * p0.x() + line.d.z() * p0.z();
    float c = p0.x() * p0.x() + p0.z() * p0.z() - r_ * r_;
    float delta = b * b - a * c;
    if (delta < EPS)
        return INFINITY;
    float t = (-b - std::sqrt(delta)) / a;
    if (t < EPS)
        return INFINITY;
    float y = p0.y() + t * line.d.y();
    if (y > h_ + EPS || y < -EPS) {
        bool its = false;
        float dist = intersects_base(line, false);
        if (dist < INFINITY) {
            t = dist;
            its = true;
        }
        dist = intersects_base(line, true);
        if (dist < INFINITY && dist > EPS && t >= dist) {
            t = dist;
            its = true;
        }
        if (!its)
            return INFINITY;
    }
    return t;

}

Line Cylinder::get_normal(const Point& p) const {
    if (p.x() < cb_.x() + r_ && p.x() > cb_.x() - r_ && p.z() < cb_.z() + r_ && p.z() > cb_.z() - r_) {
        if (p.y() < cb_.y() + h_ + EPS && p.y() > cb_.y() + h_ - EPS)
            return {p, Vector::up()};
        if (p.y() < cb_.y() + EPS && p.y() > cb_.y() - EPS)
            return {p, Vector::down()};
    }
    Vector v = p - Vector{cb_.x(), p.y(), cb_.z()};
    return {p, v.normalized()};
}

TexPixel Cylinder::get_tex(const Point& p) const {
    return tex_.get_tex(p.x(), p.y());
}

float Cylinder::intersects_base(const Line& line, bool bottom) const {
    const auto& c = bottom ? cb_ : ct_;
    const auto& N = get_normal(c);
    Point p0 = line.o - c;
    float D = -(N.d * (c - cb_));

    if (std::fabs(N.d * line.d) < EPS)
        return INFINITY;

    float dist = -(N.d * p0 + D) / (N.d * line.d);

    if (dist < EPS)
        return INFINITY;

    Point p = p0 + dist * line.d;
    if (p.x() * p.x() + p.z() * p.z() - r_ * r_ > EPS)
        return INFINITY;

    return dist;
}
