//
// Created by parsy_b on 3/2/20.
//

#ifndef RAYTRACER_INTERSECTION_H
#define RAYTRACER_INTERSECTION_H

#include "Solid.h"

struct Intersection {
    Intersection(double d_, const solid_ptr& s_) : d(d_), s(s_) {}

    double d;
    const solid_ptr& s;
};

#endif //RAYTRACER_TYPES_H
