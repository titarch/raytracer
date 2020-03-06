//
// Created by parsy_b on 3/6/20.
//

#include "Wrapper.h"
#include "../../engine/ray.h"

float Wrapper::intersects(const Line& line) const {
    Intersection its = ray::cast_ray(solids_, line);
//    last_solid_ = its.s;
    return its.d;
}

Line Wrapper::get_normal(const Point& p) const {
    return last_solid_->get_normal(p);
}

TexPixel Wrapper::get_tex(const Point& p) const {
    return last_solid_->get_tex(p);
}
