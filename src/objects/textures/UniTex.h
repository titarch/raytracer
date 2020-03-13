//
// Created by parsy_b on 3/2/20.
//

#ifndef RAYTRACER_UNITEX_H
#define RAYTRACER_UNITEX_H

#include "TexMat.h"

class UniTex : public TexMat {
public:
    UniTex(const Color& ka, double kd, double ks, double ns);
    TexPixel get_tex(double x, double y) override;

private:
    Color ka_;
    double kd_;
    double ks_;
    double ns_;
    TexPixel tp_;
};

#endif //RAYTRACER_UNITEX_H
