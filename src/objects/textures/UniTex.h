//
// Created by parsy_b on 3/2/20.
//

#ifndef RAYTRACER_UNITEX_H
#define RAYTRACER_UNITEX_H

#include "TexMat.h"

class UniTex : public TexMat {
public:
    UniTex(const Color& ka, float kd, float ks, float ns);
    TexPixel get_tex(float x, float y) override;

private:
    Color ka_;
    float kd_;
    float ks_;
    float ns_;
    TexPixel tp_;
};

#endif //RAYTRACER_UNITEX_H
