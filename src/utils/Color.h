//
// Created by parsy_b on 2/12/20.
//

#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H

#include <cstdint>
#include "Vector.h"

struct Color {
    uint8_t r, g, b;

    explicit Color(uint8_t r_ = 0, uint8_t g_ = 0, uint8_t b_ = 0) : r(r_), g(g_), b(b_) {}

    [[nodiscard]] Vector to_vect() const {
        return Vector((double) r / 255, (double) g / 255, (double) b / 255);
    }

    static uint8_t color_clamp(double k) {
        if (k < 0)
            return 0u;
        if (k > 255)
            return 255u;
        return (uint8_t) k;
    }

    static Color from_vect(Vector const& v) {
        return Color(color_clamp(v.x() * 255), color_clamp(v.y() * 255), color_clamp(v.z() * 255));
    }
};

#endif //RAYTRACER_COLOR_H
