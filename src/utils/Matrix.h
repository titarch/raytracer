//
// Created by parsy_b on 3/5/20.
//

#include <array>
#include <cmath>
#include "Vector.h"

#ifndef RAYTRACER_MATRIX_H
#define RAYTRACER_MATRIX_H

template<typename T, size_t N>
class Matrix {
public:
    using row_t = std::array<T, N>;
    using grid_t = std::array<row_t, N>;

    Matrix(grid_t const& grid) : grid_(grid) {}

    Matrix t() {
        Matrix t{{}};
        for (size_t i = 0; i < N; ++i)
            for (size_t j = 0; j < N; ++j)
                t.grid_[i][j] = grid_[j][i];
        return t;
    }

    friend Vector operator*(Matrix const& m, Vector const& v) {
        Vector vp;
        for (size_t i = 0; i < 3; ++i)
            vp[i] = Vector{m.grid_[i][0], m.grid_[i][1], m.grid_[i][2]} * v;
        return vp;
    }

    static Matrix R(Vector const& u, double angle) {
        throw "Not implemented";
    }

private:
    grid_t grid_;
};

using Mat3f = Matrix<double, 3>;

template<>
inline Mat3f Mat3f::R(Vector const& u, double angle) {
    double c = cos(angle);
    double s = sin(angle);

    return Mat3f{Mat3f::grid_t{
            Mat3f::row_t{u[0] * u[0] * (1 - c) + c, u[0] * u[1] * (1 - c) - u[2] * s, u[0] * u[2] * (1 - c) + u[1] * s},
            {u[0] * u[1] * (1 - c) + u[2] * s, u[1] * u[1] * (1 - c) + c, u[1] * u[2] * (1 - c) - u[0] * s},
            {u[0] * u[2] * (1 - c) - u[1] * s, u[1] * u[2] * (1 - c) + u[0] * s, u[2] * u[2] * (1 - c) + c}
    }};
}

#endif //RAYTRACER_MATRIX_H
