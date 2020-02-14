//
// Created by parsy_b on 2/14/20.
//

#include "Camera.h"

Camera::Camera(const Point& pos, const Point& target, float x, float y, float zmin) : pos_(pos), target_(target),
                                                                                      up_(Vector::up()), x_(x), y_(y),
                                                                                      zmin_(zmin) {}

float Camera::width() {
    return zmin_ * tanf(x_);
}

float Camera::height() {
    return zmin_ * tanf(y_);
}

const Point& Camera::getPos() const {
    return pos_;
}

const Point& Camera::getTarget() const {
    return target_;
}

float Camera::getZmin() const {
    return zmin_;
}
