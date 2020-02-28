//
// Created by parsy_b on 2/14/20.
//

#ifndef RAYTRACER_OBJECTS_H
#define RAYTRACER_OBJECTS_H

#include "Point.h"
#include "Vector.h"
#include "Textures.h"

#define EPS 1e-3

struct Line {
    Line(Point const& origin, Vector const& direction) : o(origin), d(direction) {}

    Point o;
    Vector d;
};


class Solid {
public:
    explicit Solid(Point const& pos, TexMat& tex) : pos_(pos), tex_(tex) {}

    virtual float intersects(Line const& line) const = 0;

    virtual Line get_normal(Point const& p) const = 0;

    virtual TexPixel get_tex(Point const& p) const = 0;

protected:
    Point pos_;
    TexMat& tex_;
};

class Sphere : public Solid {
public:
    Sphere(const Point& pos, TexMat& tex, float r) : Solid(pos, tex), r_(r) {}

    float intersects(Line const& line) const override;

    Line get_normal(Point const& p) const override;

    TexPixel get_tex(Point const& p) const override;

protected:
    float r_;
};

class Plane : public Solid {
public:
    Plane(const Point& pos, TexMat& tex, const Vector& norm) : Solid(pos, tex), norm_(norm) {}

    float intersects(Line const& line) const override;

    Line get_normal(Point const& p) const override;

    TexPixel get_tex(Point const& p) const override;

protected:
    Vector norm_;
};

struct Intersection {
    Intersection(float d_, Solid *s_) : d(d_), s(s_) {}

    float d;
    Solid *s;
};

class Triangle : public Solid {
public:
    Triangle(TexMat& tex, Point const& v0, Point const& v1, Point const& v2) : Solid(v0, tex), v0_(v0), v1_(v1),
                                                                               v2_(v2), e0_(v1 - v0), e1_(v2 - v1),
                                                                               e2_(v0 - v2), norm_() {
        norm_ = -((v1 - v0) ^ (v2 -v0)).normalized();
    }

    float intersects(const Line& line) const override;

    Line get_normal(const Point& p) const override;

    TexPixel get_tex(const Point& p) const override;

protected:
    Point v0_, v1_, v2_;
    Vector e0_, e1_, e2_;
    Vector norm_;
};

#endif //RAYTRACER_OBJECTS_H
