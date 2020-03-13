//
// Created by parsy_b on 3/2/20.
//

#include "UniTex.h"

UniTex::UniTex(const Color& ka, double kd, double ks, double ns) : ka_(ka), kd_(kd), ks_(ks), ns_(ns),
                                                                tp_(ka, kd, ks, ns) {}

TexPixel UniTex::get_tex(double x, double y) {
    (void) x;
    (void) y;
    return tp_;
}
