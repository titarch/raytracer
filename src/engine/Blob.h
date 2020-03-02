//
// Created by parsy_b on 2/28/20.
//

#ifndef RAYTRACER_BLOB_H
#define RAYTRACER_BLOB_H

#include <functional>
#include "Scene.h"
#include "../utils/Point.h"
#include "../objects/textures/TexMat.h"

struct ChargedPoint {
    Point p;
    float e;

    ChargedPoint(const Point &p, float e) : p(p), e(e) {}
};

struct SpaceCube {
    Point c; // left-down-back edge of the cube
    float d;

    SpaceCube(const Point &c, float d) : c(c), d(d) {}
};

class Blob;

using charged_points = std::vector<ChargedPoint>;
using potential_func = std::function<float(Point const &, Blob const &)>;

class Blob {
public:
    Blob(charged_points &&cps, potential_func const &pf,
         SpaceCube const &sc, float step, float limit) : cps_(cps), pf_(pf), sc_(sc), step_(step), limit_(limit),
                                                         nb_cubes_(0), curr_cube_(sc.c) {
        nb_cubes_ = (unsigned) (sc.d / step);
    }

    void render(Scene &s, TexMat& tex);
    static float pf_linear(Point const &p, Blob const &b);
    static float pf_square(Point const &p, Blob const &b);

private:
    charged_points cps_;
    const potential_func &pf_;
    SpaceCube sc_;
    float step_, limit_;
    unsigned nb_cubes_;
    Point curr_cube_;

    [[nodiscard]] Point cube_corner(uint8_t corner) const;
    [[nodiscard]] Point middle(uint8_t x, uint8_t y) const;
    [[nodiscard]] Point cube_edge(uint8_t edge) const;
    [[nodiscard]] float potential(uint8_t corner) const;
    [[nodiscard]] uint8_t get_index() const;
    void add_triangles(Scene &s, TexMat &t) const;
};


#endif //RAYTRACER_BLOB_H
