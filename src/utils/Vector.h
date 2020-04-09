//
// Created by parsy_b on 2/12/20.
//

#ifndef RAYTRACER_VECTOR_H
#define RAYTRACER_VECTOR_H


#include <cmath>
#include <ostream>

class Vector {
public:
    explicit Vector(double x = 0, double y = 0, double z = 0) : x_(x), y_(y), z_(z) {}

    [[nodiscard]] double sqrMagnitude() const {
        return x_ * x_ + y_ * y_ + z_ * z_;
    }

    [[nodiscard]] double magnitude() const {
        return std::sqrt(sqrMagnitude());
    }

    [[nodiscard]] Vector normalized() const {
        Vector copy(*this);
        copy /= magnitude();
        return copy;
    }

    double& operator[](size_t idx) {
        switch (idx) {
            case 0:
                return x_;
            case 1:
                return y_;
            case 2:
                return z_;
            default:
                throw std::out_of_range("Valid indices for Vector are 0, 1 or 2");
        }
    }

    double operator[](size_t idx) const {
        switch (idx) {
            case 0:
                return x_;
            case 1:
                return y_;
            case 2:
                return z_;
            default:
                throw std::out_of_range("Valid indices for Vector are 0, 1 or 2");
        }
    }

    Vector& operator+=(Vector const& rhs) {
        x_ += rhs.x_;
        y_ += rhs.y_;
        z_ += rhs.z_;
        return *this;
    }

    Vector operator-() const {
        return Vector(-x_, -y_, -z_);
    }

    Vector& operator-=(Vector const& rhs) {
        x_ -= rhs.x_;
        y_ -= rhs.y_;
        z_ -= rhs.z_;
        return *this;
    }

    Vector& operator*=(double k) {
        x_ *= k;
        y_ *= k;
        z_ *= k;
        return *this;
    }

    Vector& operator/=(double k) {
        x_ /= k;
        y_ /= k;
        z_ /= k;
        return *this;
    }

    Vector& operator%=(Vector const& rhs) {
        x_ *= rhs.x_;
        y_ *= rhs.y_;
        z_ *= rhs.z_;
        return *this;
    }

    Vector& operator%=(double k) {
        x_ = std::pow(x_, k);
        y_ = std::pow(y_, k);
        z_ = std::pow(z_, k);
        return *this;
    }

    Vector& operator^=(Vector const& rhs) {
        double x = y_ * rhs.z_ - z_ * rhs.y_;
        double y = z_ * rhs.x_ - x_ * rhs.z_;
        double z = x_ * rhs.y_ - y_ * rhs.x_;
        x_ = x;
        y_ = y;
        z_ = z;
        return *this;
    }

    friend inline double operator*(Vector const& lhs, Vector const& rhs) {
        return lhs.x_ * rhs.x_ + lhs.y_ * rhs.y_ + lhs.z_ * rhs.z_;
    }

    friend std::ostream& operator<<(std::ostream& os, Vector const& v) {
        return os << '(' << v.x_ << ' ' << v.y_ << ' ' << v.z_ << ')';
    }

    static Vector zero() {
        return Vector();
    }

    static Vector one() {
        return Vector(1.f, 1.f, 1.f);
    }

    static Vector right() {
        return Vector(1, 0, 0);
    }

    static Vector left() {
        return Vector(-1, 0, 0);
    }

    static Vector up() {
        return Vector(0, 1, 0);
    }

    static Vector down() {
        return Vector(0, -1, 0);
    }

    static Vector forward() {
        return Vector(0, 0, 1);
    }

    static Vector back() {
        return Vector(0, 0, -1);
    }

    [[nodiscard]] double x() const {
        return x_;
    }

    [[nodiscard]] double y() const {
        return y_;
    }

    [[nodiscard]] double z() const {
        return z_;
    }

    double x_, y_, z_;
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

inline Vector operator%(Vector lhs, Vector const& rhs) {
    lhs %= rhs;
    return lhs;
}

inline Vector operator%(Vector lhs, double rhs) {
    lhs %= rhs;
    return lhs;
}

inline Vector operator^(Vector lhs, Vector const& rhs) {
    lhs ^= rhs;
    return lhs;
}

#endif //RAYTRACER_VECTOR_H
