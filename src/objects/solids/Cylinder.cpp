//
// Created by parsy_b on 3/6/20.
//

#include "Cylinder.h"

double Cylinder::intersects(const Line& line) const {
    auto dp = line.o - cb_;
    auto e = line.d - (line.d * cd_) * cd_;
    double a = e.sqrMagnitude();
    auto f = dp - (dp * cd_) * cd_;
    double b = e * f;
    double c = f.sqrMagnitude() - r_ * r_;

    double delta = b * b - a * c;
    if (delta < EPS)
        return Inf;
    double t = (-b - std::sqrt(delta)) / a;
    if (t < EPS)
        return Inf;
    auto q = line.o + t * line.d;
    if (cd_ * (q - cb_) <= 0 || cd_ * (q - ct_) >= 0) {
        bool changed = false;
        double dist = intersects_base(line, false);
        if (dist < Inf) {
            t = dist;
            changed = true;
        }
        dist = intersects_base(line, true);
        if ((dist < Inf && !changed) || dist < t) {
            t = dist;
            changed = true;
        }
        if (!changed)
            return Inf;
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
    return {p, v.normalized()};
}

TexPixel Cylinder::get_tex(const Point& p) const {
    return tex_->get_tex(p.x(), p.y());
}

double Cylinder::intersects_base(const Line& line, bool bottom) const {
    const auto& c = bottom ? cb_ : ct_;
    const auto& n = bottom ? -cd_ : cd_;

    Point p0 = line.o - c;
    double denom = n * line.d;
    if (std::fabs(denom) < EPS)
        return Inf;

    double dist = (-p0 * n) / denom;
    if (dist < EPS)
        return Inf;
    Point p = line.o + dist * line.d;

    if ((p - c).sqrMagnitude() - r_ * r_ > EPS)
        return Inf;

    return dist;
}
