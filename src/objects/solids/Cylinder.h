//
// Created by parsy_b on 3/6/20.
//

#ifndef RAYTRACER_CYLINDER_H
#define RAYTRACER_CYLINDER_H


#include "Solid.h"

class Cylinder : public Solid {
public:
    Cylinder(const Point& cb, texmat_ptr const& tex, const Vector& d, double r) : Solid(cb, tex), cb_(cb), r_(r) {
        cd_ = d.normalized();
        h_ = d.magnitude();
        ct_ = cb_ + h_ * cd_;
    }

    double intersects(const Line& line) const override;
    Line get_normal(const Point& p) const override;
    TexPixel get_tex(const Point& p) const override;
private:
    Point cb_;
    double r_;
    Vector cd_;
    double h_;
    Point ct_;

    double intersects_base(const Line& line, bool bottom) const;
};


#endif //RAYTRACER_CYLINDER_H
