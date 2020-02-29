//
// Created by parsy_b on 2/28/20.
//

#include "Blob.h"

Point Blob::cube_edge(uint8_t edge) const {
    switch (edge) {
        case 0:
            return curr_cube_;
        case 1:
            return curr_cube_ + Vector::right();
        case 2:
            return cube_edge(1) + Vector::forward();
        case 3:
            return curr_cube_ + Vector::forward();
        case 4:
            return curr_cube_ + Vector::up();
        case 5:
            return cube_edge(1) + Vector::up();
        case 6:
            return cube_edge(5) + Vector::forward();
        case 7:
            return cube_edge(3) + Vector::up();
        default:
            return Vector();
    }
}

float Blob::potential(uint8_t edge) const {
    return pf_(cube_edge(edge));
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
