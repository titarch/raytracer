//
// Created by parsy_b on 2/14/20.
//

#include "Camera.h"
#include <cmath>

Camera::Camera(const Point& pos, const Vector& forward, const Vector& up,
               double x, double y, double zmin) : pos_(pos), forward_(forward), up_(up), x_(x), y_(y), zmin_(zmin) {}

double Camera::width() {
    return 2 * zmin_ * tanf(x_ / 2);
}

double Camera::height() {
    return 2 * zmin_ * tanf(y_ / 2);
}

const Point& Camera::getPos() const {
    return pos_;
}

double Camera::getZmin() const {
    return zmin_;
}

void Camera::setPos(const Point& pos) {
    pos_ = pos;
}

void Camera::move(const Vector& d) {
    pos_ += d * 0.1;
}

void Camera::rotate(Mat3f const& mat) {
    up_ = mat * up_;
    forward_ = mat * forward_;
}

Vector Camera::left() const {
    return forward_ ^ up_;
}

Vector Camera::right() const {
    return up_ ^ forward_;
}

Vector Camera::down() const {
    return -up_;
}

Vector Camera::up() const {
    return up_;
}

Vector Camera::back() const {
    return -forward_;
}

Vector Camera::forward() const {
    return forward_;
}