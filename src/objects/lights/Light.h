//
// Created by parsy_b on 3/2/20.
//

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H

#include "../../utils/Point.h"

class Light {
public:
    Vector pos() const;

protected:
    Light(const Point& pos) : pos_(pos) {}
    Point pos_;
};

#endif //RAYTRACER_LIGHT_H
