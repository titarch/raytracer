//
// Created by parsy_b on 3/6/20.
//

#ifndef RAYTRACER_CYLINDER_H
#define RAYTRACER_CYLINDER_H


#include "Solid.h"

class Cylinder : public Solid {
public:
    float intersects(const Line& line) const override;
    Line get_normal(const Point& p) const override;
    TexPixel get_tex(const Point& p) const override;
private:

};


#endif //RAYTRACER_CYLINDER_H
