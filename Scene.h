//
// Created by parsy_b on 2/12/20.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include <vector>
#include "objects.h"
#include "lights.h"
#include "Camera.h"
#include "Image.h"

class Scene {
public:
    Scene(Camera& cam);
    void add_solid(Solid *s);
    void add_light(Light *l);
    Intersection cast_ray(Line const& ray);
    Color get_light_value(Intersection const& its, Line const& ray);
    Image render(unsigned width, unsigned height);
protected:
    std::vector<Solid*> solids_;
    std::vector<Light*> lights_;
    Camera& cam_;
    float w_;
    float h_;
    Point center_, tl_, br_, pos_;
};


#endif //RAYTRACER_SCENE_H
