//
// Created by parsy_b on 2/14/20.
//

#ifndef RAYTRACER_TEXTURES_H
#define RAYTRACER_TEXTURES_H

#include "Color.h"
#include "Vector.h"

struct TexPixel {
    TexPixel(Color const& ka_, float kd_, float ks_, float ns_) : ka(ka_), kd(kd_), ks(ks_), ns(ns_) {}

    Color ka;
    float kd;
    float ks;
    float ns;
};

class TexMat {
public:
    virtual TexPixel get_tex(float x, float y) = 0;
};

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

#endif //RAYTRACER_TEXTURES_H
