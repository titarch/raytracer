//
// Created by parsy_b on 3/2/20.
//

#ifndef RAYTRACER_TRIANGLE_H
#define RAYTRACER_TRIANGLE_H

#include "Solid.h"

class Triangle : public Solid {
public:
    Triangle(texmat_ptr const& tex, Point const& v0, Point const& v1, Point const& v2) : Solid(v0, tex), v0_(v0),
                                                                                         v1_(v1), v2_(v2), e0_(v1 - v0),
                                                                                         e1_(v2 - v1), e2_(v0 - v2),
                                                                                         norm_() {
        norm_ = -((v1 - v0) ^ (v2 - v0)).normalized();
    }

    double intersects(const Line& line) const override;
    Line get_normal(const Point& p) const override;
    TexPixel get_tex(const Point& p) const override;

protected:
    Point v0_, v1_, v2_;
    Vector e0_, e1_, e2_;
    Vector norm_;
};

#endif //RAYTRACER_TRIANGLE_H
