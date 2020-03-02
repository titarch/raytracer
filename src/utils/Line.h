//
// Created by parsy_b on 3/2/20.
//

#ifndef RAYTRACER_LINE_H
#define RAYTRACER_LINE_H

#include "Point.h"

struct Line {
    Line(Point const& origin, Vector const& direction) : o(origin), d(direction) {}

    Point o;
    Vector d;
};

#endif //RAYTRACER_LINE_H
