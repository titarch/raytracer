//
// Created by parsy_b on 2/12/20.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include <vector>
#include "Camera.h"
#include "Image.h"
#include "solids/Solid.h"
#include "lights/Light.h"
#include "solids/Intersection.h"

#define REFLECTION_REC_LVL_MAX 3

class Scene {
public:
    explicit Scene(camera_ptr cam);
    void update_view();
    Intersection cast_ray(Line const& ray);
    Vector refract_ray(Intersection const& its, Line const& ray, int rec_lvl);
    Vector get_light_value(Intersection const& its, Line const& ray, int rec_lvl = 0);
    Image render(unsigned width, unsigned height);
    void render_rt(unsigned int width, unsigned int height);
    static Scene load(std::string const& path);
    static Scene demo();

    template<typename S, typename ...Args>
    Scene& emplace_solid(Args&& ... args) {
        solids_.push_back(std::make_unique<S>(args...));
        return *this;
    }

    template<typename S>
    Scene& push_solid(S const& solid) {
        solids_.push_back(std::make_unique<S>(solid));
        return *this;
    }

    template<typename L, typename ...Args>
    Scene& emplace_light(Args&& ... args) {
        lights_.push_back(std::make_unique<L>(args...));
        return *this;
    }

    template<typename L>
    Scene& push_light(L const& light) {
        lights_.push_back(std::make_unique<L>(light));
        return *this;
    }

    [[nodiscard]] bool dark() const { return lights_.empty(); }

protected:
    camera_ptr cam_;
    solids solids_;
    lights lights_;
    double w_;
    double h_;
    Point center_, tl_;

};


#endif //RAYTRACER_SCENE_H
