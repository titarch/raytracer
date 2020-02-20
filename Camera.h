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

    [[nodiscard]] const Point& getPos() const;

    [[nodiscard]] const Point& getTarget() const;

    [[nodiscard]] float getZmin() const;

    void setPos(const Point& pos);

    void setTarget(const Point& target);

    void move(Vector const& d);

    void rotate(float phi, float theta, float psi);


private:
    Point pos_;
    Point target_;
    Vector up_;
    float x_;
    float y_;
    float zmin_;
};


#endif //RAYTRACER_CAMERA_H
