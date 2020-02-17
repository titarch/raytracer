//
// Created by parsy_b on 2/14/20.
//

#include "Camera.h"

Camera::Camera(const Point& pos, const Point& target, float x, float y, float zmin) : pos_(pos), target_(target),
                                                                                      up_(Vector::up()), x_(x), y_(y),
                                                                                      zmin_(zmin) {}

float Camera::width() {
    return 2 * zmin_ * tanf(x_ / 2);
}

float Camera::height() {
    return 2 *  zmin_ * tanf(y_ / 2);
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
