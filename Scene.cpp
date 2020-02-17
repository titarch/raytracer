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

Color Scene::get_light_value(Intersection const& its, Line const& ray) {
    Point p = ray.o + ray.d * its.d;
    TexPixel tp = its.s->get_tex(p);
    Line norm = its.s->get_normal(p);
    Vector reflection = ray.d - 2 * (ray.d * norm.d) * norm.d;
    Vector lum;
    for (auto l : lights_) {
        Vector l_dir = (l->pos() - p).normalized();
        Intersection lits = cast_ray({p, l_dir});
        if (lits.s != nullptr && lits.d * lits.d < (l->pos() - p).sqrMagnitude())
            continue;
        Vector local_lum = tp.kd * tp.ka.to_vect() * (norm.d * l_dir) + tp.ks * Vector::one() * (-reflection * l_dir) % tp.ns;
        lum += local_lum;
    }
    return Color::from_vect(lum);
}

Image Scene::render(unsigned int width, unsigned int height) {
    Image img = Image(width, height);

    for (auto i = 0u; i < height; ++i) {
        for (auto j = 0u; j < width; ++j) {
            Point z_target = tl_ + ((float) i / height) * Vector::down() + ((float) j / width) * Vector::right();
            Vector ray_dir = (z_target - pos_).normalized();
            Line ray = {z_target, ray_dir};
            Intersection its = cast_ray(ray);

            Color c;
            if (its.s != nullptr)
                c = get_light_value(its, ray);
            img.set_pix(i, j, c);
        }
    }
    return img;
}

