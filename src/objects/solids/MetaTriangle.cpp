//
// Created by parsy_b on 3/6/20.
//

#include "MetaTriangle.h"

Line MetaTriangle::get_normal(const Point& p) const {
    return {p, grad_(p, blob_)};
}

