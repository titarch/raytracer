//
// Created by parsy_b on 3/6/20.
//

#include "Cylinder.h"

float Cylinder::intersects(const Line& line) const {
    return 0;
}

Line Cylinder::get_normal(const Point& p) const {
    return Line(Vector(), Vector());
}

TexPixel Cylinder::get_tex(const Point& p) const {
    return TexPixel(Color(), 0, 0, 0);
}
