//
// Created by bparsy on 4/9/20.
//

#ifndef RAYTRACER_TRANSTEX_H
#define RAYTRACER_TRANSTEX_H


#include "UniTex.h"

class TransTex : public TexMat {
public:
    TransTex(double n) : n_(n) {}

    [[nodiscard]] double refractive_index() const {
        return n_;
    }

    TexPixel get_tex(double x, double y) override {
        (void)x;
        (void)y;
        return TexPixel(Color(), 0, 0, 0);
    }

protected:
    double n_;
};


#endif //RAYTRACER_TRANSTEX_H
