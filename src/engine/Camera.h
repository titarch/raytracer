//
// Created by parsy_b on 2/14/20.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H


#include "../utils/Point.h"
#include <memory>

class Camera {
public:
    Camera(const Point& pos, const Vector& forward, const Vector& up, double x, double y, double zmin);
    double width();
    double height();
    [[nodiscard]] Vector left() const;
    [[nodiscard]] Vector right() const;
    [[nodiscard]] Vector up() const;
    [[nodiscard]] Vector down() const;
    [[nodiscard]] Vector back() const;
    [[nodiscard]] Vector forward() const;
    [[nodiscard]] const Point& getPos() const;
    [[nodiscard]] double getZmin() const;
    void setPos(const Point& pos);
    void move(Vector const& d);
    void rotate(double theta, double phi, double psi);

private:
    Point pos_;
    Vector forward_, up_;
    double x_;
    double y_;
    double zmin_;
};

using camera_ptr = std::unique_ptr<Camera>;

#endif //RAYTRACER_CAMERA_H
