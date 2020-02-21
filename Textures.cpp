//
// Created by parsy_b on 2/14/20.
//

#include "Textures.h"

TexPixel UniTex::get_tex(float x, float y) {
    return tp_;
}

UniTex::UniTex(const Color& ka, float kd, float ks, float ns) : ka_(ka), kd_(kd), ks_(ks), ns_(ns),
                                                                tp_(ka, kd, ks, ns) {}
