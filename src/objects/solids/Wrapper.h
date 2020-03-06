//
// Created by parsy_b on 3/6/20.
//

#ifndef RAYTRACER_WRAPPER_H
#define RAYTRACER_WRAPPER_H


#include <vector>
#include "Solid.h"

class Wrapper : public Solid {
public:
    Wrapper(const Point& pos, TexMat& tex, const std::vector<Solid*>& solids) : Solid(pos, tex), solids_(solids),
                                                                                last_solid_(nullptr) {}

    float intersects(const Line& line) const override;
    Line get_normal(const Point& p) const override;
    TexPixel get_tex(const Point& p) const override;
private:
    std::vector<Solid*> solids_;
    Solid* last_solid_;
};


#endif //RAYTRACER_WRAPPER_H
