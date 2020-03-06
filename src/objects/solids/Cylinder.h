//
// Created by parsy_b on 3/6/20.
//

#ifndef RAYTRACER_CYLINDER_H
#define RAYTRACER_CYLINDER_H


#include "Solid.h"

class Cylinder : public Solid {
public:
    Cylinder(const Point& pos, TexMat& tex, const Point& cb, float r, float h) : Solid(pos, tex), cb_(cb),
                                                                                 ct_(cb + h * Vector::up()), r_(r),
                                                                                 h_(h) {}

    float intersects(const Line& line) const override;
    Line get_normal(const Point& p) const override;
    TexPixel get_tex(const Point& p) const override;
private:
    Point cb_, ct_;
    float r_, h_;

    float intersects_base(const Line& line, bool bottom) const;
};


#endif //RAYTRACER_CYLINDER_H
