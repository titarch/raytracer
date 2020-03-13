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
    void add_solid(Solid *s);
    void add_light(Light *l);
    Intersection cast_ray(Line const& ray);
    Vector get_light_value(Intersection const& its, Line const& ray, int rec_lvl = 0);
    Image render(unsigned width, unsigned height);
    void render_rt(unsigned int width, unsigned int height);
    void load(const char* path);
protected:
    Camera& cam_;
    std::vector<Solid *> solids_;
    std::vector<Light *> lights_;
    double w_;
    double h_;
    Point center_, tl_;

};


#endif //RAYTRACER_SCENE_H
