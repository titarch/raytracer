//
// Created by parsy_b on 3/6/20.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H


#include <vector>
#include "../objects/solids/Intersection.h"

namespace ray {
    struct Compare {
        float val;
        int index;
    };

    Intersection cast_ray(std::vector<Solid*> const& solids, const Line& ray) {
        float dists[solids.size()];
#pragma omp simd
        for (unsigned i = 0u; i < solids.size(); ++i)
            dists[i] = solids[i]->intersects(ray);
        Compare min{INFINITY, -1};
        for (auto k = 0u; k < solids.size(); ++k) {
            if (dists[k] < min.val) {
                min.val = dists[k];
                min.index = k;
            }
        }
        if (min.index == -1)
            return Intersection{-1, nullptr};
        return Intersection{min.val, solids[min.index]};
    }
}

#endif //RAYTRACER_RAY_H