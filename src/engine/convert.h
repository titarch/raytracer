//
// Created by bparsy on 3/11/20.
//

#ifndef RAYTRACER_CONVERT_H
#define RAYTRACER_CONVERT_H

#include <yaml-cpp/yaml.h>
#include "../utils/Vector.h"

namespace YAML {
    template<>
    struct convert<Vector> {
        static bool decode(const Node& node, Vector& rhs) {
            if (!node.IsSequence() || node.size() != 3) {
                return false;
            }

            rhs.x_ = node[0].as<float>();
            rhs.y_ = node[1].as<float>();
            rhs.z_ = node[2].as<float>();
            return true;
        }
    };
}
#endif //RAYTRACER_CONVERT_H