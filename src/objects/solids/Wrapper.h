//
// Created by parsy_b on 3/6/20.
//

#ifndef RAYTRACER_WRAPPER_H
#define RAYTRACER_WRAPPER_H


#include <utility>
#include <vector>
#include "Solid.h"

class Wrapper : public Solid {
public:
    Wrapper(const Point& pos, TexMat& tex, solids solids) : Solid(pos, tex), solids_(std::move(solids)),
                                                            last_solid_(nullptr) {}

    double intersects(const Line& line) const override;
    Line get_normal(const Point& p) const override;
    TexPixel get_tex(const Point& p) const override;
private:
    solids solids_;
    solid_ptr last_solid_;
};


#endif //RAYTRACER_WRAPPER_H
