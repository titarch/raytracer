//
// Created by parsy_b on 2/28/20.
//

#ifndef RAYTRACER_BLOB_H
#define RAYTRACER_BLOB_H

#include <functional>
#include "Point.h"

struct ChargedPoint {
    Point p;
    float e;

    ChargedPoint(const Point& p, float e) : p(p), e(e) {}
};

struct SpaceCube {
    Point c; // left-down-back edge of the cube
    float d;

    SpaceCube(const Point& c, float d) : c(c), d(d) {}
};

using potential_func = std::function<float (Point)>;
using charged_points = std::vector<ChargedPoint>;

class Blob {
public:
    Blob(charged_points&& cps, potential_func const& pf,
         SpaceCube const& sc, float step, float limit) : cps_(cps), pf_(pf), sc_(sc), step_(step), limit_(limit),
                                                         nb_cubes_(0), curr_cube_(sc.c) {
        nb_cubes_ = (unsigned) (sc.d / step);
    }

private:
    charged_points cps_;
    const potential_func& pf_;
    SpaceCube sc_;
    float step_, limit_;
    unsigned nb_cubes_;
    Point curr_cube_;

    Point cube_edge(uint8_t edge) const;
    float potential(uint8_t edge) const;
    uint8_t get_index() const;
};


#endif //RAYTRACER_BLOB_H
