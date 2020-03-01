//
// Created by parsy_b on 2/28/20.
//

#include "Blob.h"
#include "cubetrig.h"

Point Blob::cube_corner(uint8_t edge) const {
    switch (edge) {
        case 0:
            return curr_cube_;
        case 1:
            return curr_cube_ + Vector::right();
        case 2:
            return cube_corner(1) + Vector::forward();
        case 3:
            return curr_cube_ + Vector::forward();
        case 4:
            return curr_cube_ + Vector::up();
        case 5:
            return cube_corner(1) + Vector::up();
        case 6:
            return cube_corner(5) + Vector::forward();
        case 7:
            return cube_corner(3) + Vector::up();
        default:
            return Point();
    }
}

Point Blob::middle(uint8_t x, uint8_t y) const {
    return (cube_corner(x) + cube_corner(y)) / 2;
}

Point Blob::cube_edge(uint8_t edge) const {
    switch (edge) {
        case 0:
            return middle(0, 1);
        case 1:
            return middle(1, 2);
        case 2:
            return middle(2, 3);
        case 3:
            return middle(3, 0);
        case 4:
            return middle(4, 5);
        case 5:
            return middle(5, 6);
        case 6:
            return middle(6, 7);
        case 7:
            return middle(7, 4);
        case 8:
            return middle(4, 0);
        case 9:
            return middle(5, 1);
        case 10:
            return middle(2, 6);
        case 11:
            return middle(3, 7);
        default:
            return Point();
    }
}

float Blob::potential(uint8_t corner) const {
    return pf_(cube_corner(corner), *this);
}

uint8_t Blob::get_index() const {
    uint8_t index = 0;
    if (potential(0) < limit_) index |= 1u;
    if (potential(1) < limit_) index |= 2u;
    if (potential(2) < limit_) index |= 4u;
    if (potential(3) < limit_) index |= 8u;
    if (potential(4) < limit_) index |= 16u;
    if (potential(5) < limit_) index |= 32u;
    if (potential(6) < limit_) index |= 64u;
    if (potential(7) < limit_) index |= 128u;
    return index;
}

void Blob::add_triangles(Scene &s, TexMat &t) const {
    auto tc = cube_tri_conf[get_index()];

    for (auto i = 0u; i < 15u; i += 3u) {
        int e0 = tc[i];
        if (e0 < 0)
            break;
        int e1 = tc[i + 1];
        int e2 = tc[i + 2];
        const Point &v0 = cube_edge(e0);
        const Point &v1 = cube_edge(e1);
        const Point &v2 = cube_edge(e2);

        auto *tri = new Triangle(t, v0, v1, v2);
        s.add_solid(tri);
    }

}

void Blob::render(Scene &scene, TexMat &tex) {
    for (auto i = 0u; i < nb_cubes_; ++i) {
        for (auto j = 0u; j < nb_cubes_; ++j) {
            for (auto k = 0u; k < nb_cubes_; ++k) {
                curr_cube_ = sc_.c + step_ * (i * Vector::right() + j * Vector::up() + k * Vector::forward());
                add_triangles(scene, tex);
            }
        }
    }
}

float Blob::pf_linear(const Point &p, const Blob &b) {
    float e = 0;
    for (const auto &cp : b.cps_)
        e += cp.e / (cp.p - p).magnitude();
    return e;
}

float Blob::pf_square(const Point &p, const Blob &b) {
    float e = 0;
    for (const auto &cp : b.cps_)
        e += cp.e / (cp.p - p).sqrMagnitude();
    return e;
}
