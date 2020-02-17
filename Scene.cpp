//
// Created by parsy_b on 2/12/20.
//

#include "Scene.h"

Scene::Scene(Camera& cam) : cam_(cam), solids_(), lights_() {
    w_ = cam.width();
    h_ = cam.height();

    float zmin = cam.getZmin();
    pos_ = cam.getPos();
    Point tgt = cam.getTarget();

    center_ = pos_ + (tgt - pos_).normalized() * zmin;
    tl_ = center_ + (w_ / 2) * Vector::left() + (h_ / 2) * Vector::up();
    br_ = center_ + (w_ / 2) * Vector::right() + (h_ / 2) * Vector::down();
}

void Scene::add_solid(Solid *s) {
    solids_.push_back(s);
}

void Scene::add_light(Light *l) {
    lights_.push_back(l);
}

Intersection Scene::cast_ray(const Line& ray) {
    float min_dist = INFINITY;
    float min_idx = -1;
    for (auto k = 0u; k < solids_.size(); ++k) {
        float dist = solids_[k]->intersects(ray);
        if (dist >= 0 && dist < min_dist) {
            min_dist = dist;
            min_idx = k;
        }
    }
    if (min_idx == -1)
        return Intersection{-1, nullptr};
    return Intersection{min_dist, solids_[min_idx]};
}

float Scene::get_light_value(Point const& p, TexPixel const& tp, Intersection const& its) {
    Line norm = its.s->get_normal(p);
    float lum = 0;
    for (auto l : lights_) {
        Vector l_dir = (l->pos() - p).normalized();
        Intersection lits = cast_ray({p, l_dir});
        if (lits.s != nullptr  && lits.d * lits.d < (l->pos() - p).sqrMagnitude())
            continue;

        float local_lum = tp.kd * (norm.d * l_dir);
        if (local_lum < 0)
            continue;
        lum += local_lum;
    }
    return lum;
}

Image Scene::render(unsigned int width, unsigned int height) {
    Image img = Image(width, height);

    for (auto i = 0u; i < height; ++i) {
        for (auto j = 0u; j < width; ++j) {
            Point z_target = tl_ + ((float) i / height) * Vector::down() + ((float) j / width) * Vector::right();
            Vector ray_dir = (z_target - pos_).normalized();
            Intersection its = cast_ray({z_target, ray_dir});

            Color c;
            if (its.s != nullptr) {
                Point contact = z_target + ray_dir * its.d;
                TexPixel tp = its.s->get_tex(contact);
                float lum = get_light_value(contact, tp, its);

                c.r = (float) tp.ka.r * lum;
                c.g = (float) tp.ka.g * lum;
                c.b = (float) tp.ka.b * lum;
            }
            img.set_pix(i, j, c);
        }
    }
    return img;
}

