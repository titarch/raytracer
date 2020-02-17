//
// Created by parsy_b on 2/14/20.
//

#ifndef RAYTRACER_OBJECTS_H
#define RAYTRACER_OBJECTS_H

#include "Point.h"
#include "Vector.h"
#include "Textures.h"

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
    TexMat& tex_;
    Point pos_;
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

struct Intersection {
    Intersection(float d_, Solid *s_) : d(d_), s(s_) {}

    float d;
    Solid* s;
};

#endif //RAYTRACER_OBJECTS_H
