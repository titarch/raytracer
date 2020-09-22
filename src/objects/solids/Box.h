//
// Created by bparsy on 7/14/20.
//

#ifndef RAYTRACER_BOX_H
#define RAYTRACER_BOX_H

#include "Solid.h"

class Box : public Solid {
public:
    Box(Point const& bound_min, Point const& bound_max, texmat_ptr& tex,
        Vector const& up = Vector::up(), Vector const& right = Vector::right())
            : Solid((bound_min + bound_max) / 2, tex),
              bound_min_(bound_min), bound_max_(bound_max), up_(up), right_(right), forward_(right ^ up) {}

    double intersects(Line const& line) const override;
    Line get_normal(Point const& p) const override;
    TexPixel get_tex(Point const& p) const override;

protected:
    Point bound_min_, bound_max_;
    Vector up_, right_, forward_;
};


#endif //RAYTRACER_BOX_H
