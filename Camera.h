//
// Created by parsy_b on 2/14/20.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H


#include "Point.h"

class Camera {
public:
    Camera(const Point& pos, const Point& target, float x, float y, float zmin);
    float width();
    float height();

    const Point& getPos() const;

    const Point& getTarget() const;

    float getZmin() const;

private:
    Point pos_;
    Point target_;
    Vector up_;
    float x_;
    float y_;
    float zmin_;
};


#endif //RAYTRACER_CAMERA_H
