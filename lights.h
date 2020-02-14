//
// Created by parsy_b on 2/14/20.
//

#ifndef RAYTRACER_LIGHTS_H
#define RAYTRACER_LIGHTS_H

#include "Point.h"

class Light {
public:
    Light(const Point& pos) : pos_(pos) {}

    Vector pos() {
        return pos_;
    }

protected:
    Point pos_;
};

class PointLight : public Light {
public:
    PointLight(const Point& pos) : Light(pos) {}
};

#endif //RAYTRACER_LIGHTS_H
