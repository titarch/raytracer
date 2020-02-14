//
// Created by parsy_b on 2/12/20.
//

#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H

#include <cstdint>

struct Color {
    uint8_t r, g, b;

    explicit Color(uint8_t r_ = 0, uint8_t g_ = 0, uint8_t b_ = 0) : r(r_), g(g_), b(b_) {}
};

#endif //RAYTRACER_COLOR_H
