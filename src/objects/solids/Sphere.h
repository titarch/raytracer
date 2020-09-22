//
// Created by parsy_b on 3/2/20.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "Solid.h"

class Sphere : public Solid {
public:
    Sphere(const Point& pos, texmat_ptr& tex, double r) : Solid(pos, tex), r_(r) {}
    double intersects(Line const& line) const override;
    Line get_normal(Point const& p) const override;
    TexPixel get_tex(Point const& p) const override;

protected:
    double r_;
};

#endif //RAYTRACER_SPHERE_H
