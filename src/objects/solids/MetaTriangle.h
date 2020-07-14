//
// Created by parsy_b on 3/6/20.
//

#ifndef RAYTRACER_METATRIANGLE_H
#define RAYTRACER_METATRIANGLE_H


#include "Triangle.h"

#include <utility>
#include "engine/Blob.h"

class MetaTriangle : public Triangle {
public:
    MetaTriangle(texmat_ptr const& tex, const Point& v0, const Point& v1, const Point& v2,
                 const Blob& blob, potential_grad grad) : Triangle(tex, v0, v1, v2), blob_(blob),
                                                          grad_(std::move(grad)) {}

    Line get_normal(const Point& p) const override;
protected:
    const Blob& blob_;
    potential_grad grad_;
};


#endif //RAYTRACER_METATRIANGLE_H
