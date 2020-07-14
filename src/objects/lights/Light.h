//
// Created by parsy_b on 3/2/20.
//

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H

#include "utils/Point.h"
#include <memory>
#include <vector>

class Light {
public:
    Vector pos() const;

protected:
    Light(const Point& pos) : pos_(pos) {}
    Point pos_;
};

using light_ptr = std::unique_ptr<Light>;
using lights = std::vector<light_ptr>;

#endif //RAYTRACER_LIGHT_H
