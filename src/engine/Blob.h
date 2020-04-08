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
    double e;

    ChargedPoint(const Point& p, double e) : p(p), e(e) {}
};

struct SpaceCube {
    Point c; // left-down-back edge of the cube
    double d;

    SpaceCube(const Point& c, double d) : c(c), d(d) {}
};

class Blob;

using charged_points = std::vector<ChargedPoint>;
using potential_func = std::function<double(Point const&, Blob const&)>;
using potential_grad = std::function<Vector(Point const&, Blob const&)>;

class Blob {
public:
    Blob(charged_points&& cps, potential_func const& pf,
         SpaceCube const& sc, double step, double limit) : cps_(cps), pf_(pf), sc_(sc), step_(step), limit_(limit),
                                                         nb_cubes_(0), curr_cube_(sc.c) {
        nb_cubes_ = (unsigned) (sc.d / step);
    }

    void render(Scene& s, texmat_ptr const& tex);
    static double pf_linear(Point const& p, Blob const& b);
    static Vector pf_linear_grad(Point const& p, Blob const& b);
    static double pf_square(Point const& p, Blob const& b);

private:
    charged_points cps_;
    const potential_func& pf_;
    SpaceCube sc_;
    double step_, limit_;
    unsigned nb_cubes_;
    Point curr_cube_;

    [[nodiscard]] Point cube_corner(uint8_t corner) const;
    [[nodiscard]] Point middle(uint8_t x, uint8_t y) const;
    [[nodiscard]] Point cube_edge(uint8_t edge) const;
    [[nodiscard]] double potential(uint8_t corner) const;
    [[nodiscard]] uint8_t get_index() const;
    void add_triangles(Scene& s, texmat_ptr const& t) const;
};


#endif //RAYTRACER_BLOB_H
