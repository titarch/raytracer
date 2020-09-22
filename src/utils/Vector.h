//
// Created by parsy_b on 2/12/20.
//

#ifndef RAYTRACER_VECTOR_H
#define RAYTRACER_VECTOR_H

#include <eigen3/Eigen/Dense>
#include <cmath>
#include <ostream>
#include <utility>

class Vector {
public:
    explicit Vector(double x = 0, double y = 0, double z = 0) : vec_(x, y, z) {}

    explicit Vector(Eigen::Vector3d vec) : vec_(std::move(vec)) {}

    [[nodiscard]] double sqrMagnitude() const {
        return vec_.squaredNorm();
    }

    [[nodiscard]] double magnitude() const {
        return vec_.norm();
    }

    [[nodiscard]] Vector normalized() const {
        return Vector(vec_.normalized());
    }

    double& operator[](size_t idx) {
        return vec_[idx];
    }

    double operator[](size_t idx) const {
        return vec_[idx];
    }

    Vector& operator+=(Vector const& rhs) {
        vec_ += rhs.vec_;
        return *this;
    }

    Vector operator-() const {
        return Vector(-vec_);
    }

    Vector& operator-=(Vector const& rhs) {
        vec_ -= rhs.vec_;
        return *this;
    }

    Vector& operator*=(double k) {
        vec_ *=  k;
        return *this;
    }

    Vector& operator/=(Vector const& rhs) {
        vec_[0] /= rhs.vec_[0];
        vec_[1] /= rhs.vec_[1];
        vec_[2] /= rhs.vec_[2];
        return *this;
    }

    Vector& operator/=(double k) {
        vec_ /= k;
        return *this;
    }

    Vector& operator^=(Vector const& rhs) {
        vec_ = vec_.cross(rhs.vec_);
        return *this;
    }

    friend inline double operator*(Vector const& lhs, Vector const& rhs) {
        return lhs.vec_.dot(rhs.vec_);
    }

    friend inline double operator%(Vector const& lhs, Vector const& rhs) {
        return acos(lhs.normalized() * rhs.normalized());
    }

    friend std::ostream& operator<<(std::ostream& os, Vector const& v) {
        return os << '(' << v.vec_.x() << ' ' << v.vec_.y() << ' ' << v.vec_.z() << ')';
    }

    static Vector zero() {
        return Vector();
    }

    static Vector one() {
        return Vector(1.0, 1.0, 1.0);
    }

    static Vector right() {
        return Vector(1.0, 0.0, 0.0);
    }

    static Vector left() {
        return Vector(-1.0, 0.0, 0.0);
    }

    static Vector up() {
        return Vector(0.0, 1.0, 0.0);
    }

    static Vector down() {
        return Vector(0.0, -1.0, 0.0);
    }

    static Vector forward() {
        return Vector(0.0, 0.0, 1.0);
    }

    static Vector back() {
        return Vector(0.0, 0.0, -1.0);
    }

    [[nodiscard]] double x() const {
        return vec_.x();
    }

    [[nodiscard]] double y() const {
        return vec_.y();
    }

    [[nodiscard]] double z() const {
        return vec_.z();
    }

    Eigen::Vector3d vec_;
};

inline Vector operator+(Vector lhs, Vector const& rhs) {
    lhs += rhs;
    return lhs;
}

inline Vector operator-(Vector lhs, Vector const& rhs) {
    lhs -= rhs;
    return lhs;
}

inline Vector operator*(Vector lhs, double rhs) {
    lhs *= rhs;
    return lhs;
}

inline Vector operator*(double lhs, Vector rhs) {
    rhs *= lhs;
    return rhs;
}

inline Vector operator/(Vector lhs, double rhs) {
    lhs /= rhs;
    return lhs;
}

inline Vector operator/(Vector lhs, Vector const& rhs) {
    lhs /= rhs;
    return lhs;
}

inline Vector operator^(Vector lhs, Vector const& rhs) {
    lhs ^= rhs;
    return lhs;
}


#endif //RAYTRACER_VECTOR_H
