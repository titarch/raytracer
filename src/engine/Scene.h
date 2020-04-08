//
// Created by parsy_b on 2/12/20.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include <vector>
#include "Camera.h"
#include "Image.h"
#include "../objects/solids/Solid.h"
#include "../objects/lights/Light.h"
#include "../objects/solids/Intersection.h"

#define REFLECTION_REC_LVL_MAX 3

class Scene {
public:
    Scene(Camera& cam);
    void update_view();
    Intersection cast_ray(Line const& ray);
    Vector get_light_value(Intersection const& its, Line const& ray, int rec_lvl = 0);
    Image render(unsigned width, unsigned height);
    void render_rt(unsigned int width, unsigned int height);
    void load(const char* path);

    template<typename S, typename ...Args>
    Scene& emplace_solid(Args&&... args) {
        solids_.push_back(std::make_unique<S>(args...));
        return *this;
    }

    template<typename S>
    Scene& push_solid(S const& solid) {
        solids_.push_back(std::make_unique<S>(solid));
        return *this;
    }

    template<typename L, typename ...Args>
    Scene& emplace_light(Args&&... args) {
        lights_.push_back(std::make_unique<L>(args...));
        return *this;
    }

    template<typename L>
    Scene& push_light(L const& light) {
        lights_.push_back(std::make_unique<L>(light));
        return *this;
    }

protected:
    Camera& cam_;
    solids solids_;
    lights lights_;
    double w_;
    double h_;
    Point center_, tl_;

};


#endif //RAYTRACER_SCENE_H
