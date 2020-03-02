//
// Created by parsy_b on 3/2/20.
//

#ifndef RAYTRACER_POINTLIGHT_H
#define RAYTRACER_POINTLIGHT_H

#include "Light.h"

class PointLight : public Light {
public:
    PointLight(const Point& pos);
};

#endif //RAYTRACER_POINTLIGHT_H
