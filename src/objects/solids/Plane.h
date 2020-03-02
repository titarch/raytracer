//
// Created by parsy_b on 3/2/20.
//

#ifndef RAYTRACER_PLANE_H
#define RAYTRACER_PLANE_H

#include "Solid.h"

class Plane : public Solid {
public:
    Plane(const Point& pos, TexMat& tex, const Vector& norm) : Solid(pos, tex), norm_(norm) {}
    float intersects(Line const& line) const override;
    Line get_normal(Point const& p) const override;
    TexPixel get_tex(Point const& p) const override;

protected:
    Vector norm_;
};

#endif //RAYTRACER_PLANE_H
