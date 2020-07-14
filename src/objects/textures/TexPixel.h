//
// Created by parsy_b on 3/2/20.
//

#ifndef RAYTRACER_TEXPIXEL_H
#define RAYTRACER_TEXPIXEL_H

#include "utils/Color.h"

struct TexPixel {
    TexPixel(Color const& ka_, double kd_, double ks_, double ns_) : ka(ka_), kd(kd_), ks(ks_), ns(ns_) {}

    Color ka;
    double kd;
    double ks;
    double ns;
};

#endif //RAYTRACER_TEXPIXEL_H
