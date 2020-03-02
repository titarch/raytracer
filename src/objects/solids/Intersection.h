//
// Created by parsy_b on 3/2/20.
//

#ifndef RAYTRACER_INTERSECTION_H
#define RAYTRACER_INTERSECTION_H

#include "Solid.h"

struct Intersection {
    Intersection(float d_, Solid *s_) : d(d_), s(s_) {}

    float d;
    Solid *s;
};

#endif //RAYTRACER_TYPES_H
