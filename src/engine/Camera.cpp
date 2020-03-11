//
// Created by parsy_b on 2/14/20.
//

#include "Camera.h"

#include <cmath>

Camera::Camera(const Point& pos, const Vector& forward, const Vector& up,
               float x, float y, float zmin) : pos_(pos), forward_(forward), up_(up), x_(x), y_(y), zmin_(zmin) {}

float Camera::width() {
    return 2 * zmin_ * tanf(x_ / 2);
}

float Camera::height() {
    return 2 * zmin_ * tanf(y_ / 2);
}

const Point& Camera::getPos() const {
    return pos_;
}

float Camera::getZmin() const {
    return zmin_;
}

void Camera::setPos(const Point& pos) {
    pos_ = pos;
}

void Camera::move(const Vector& d) {
    pos_ += d * 0.1;
}

void Camera::rotate(float theta, float phi, float psi) {
    (void) psi;
    if (std::fabs(theta) > 0) {
        float x = forward_.x() * cosf(theta) + forward_.z() * sinf(theta);
        float z = forward_.z() * cosf(theta) - forward_.x() * sinf(theta);
        forward_ = Vector{x, forward_.y(), z}.normalized();
    }

    if (std::fabs(phi) > 0) {
        float y = up_.y() * cosf(phi) - up_.z() * sinf(phi);
        float z = up_.y() * sinf(phi) + up_.z() * cosf(phi);
        up_ = Vector{up_.x(), y, z}.normalized();

        y = -up_.z();
        z = up_.y();
        forward_ = Vector{forward_.x(), y, z}.normalized();
    }
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