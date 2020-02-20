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

void Camera::setPos(const Point& pos) {
    pos_ = pos;
}

void Camera::setTarget(const Point& target) {
    target_ = target;
}

void Camera::move(const Vector& d) {
    pos_ += d;
    target_ += d;
}

void Camera::rotate(float phi, float theta, float psi) {
    target_ += Vector::right() * phi + Vector::up() * theta;
    target_ = (target_ - pos_).normalized() + pos_;
}
