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

Color getpix(unsigned col, unsigned row) {

}

Image Scene::render(unsigned int width, unsigned int height) {
    Image img = Image(width, height);

    for (auto i = 0u; i < height; ++i) {
        for (auto j = 0u; j < width; ++j) {
            Point p = tl_ + ((float) i / height) * Vector::down() + ((float) j / width) * Vector::right();
            Vector d = (p - pos_).normalized();
            Line ray(p, d);

            float min = INFINITY;
            float minidx = -1;
            for (auto k = 0u; k < solids_.size(); ++k) {
                float dt = solids_[k]->intersects(ray);
                if (dt >= 0 && dt < min) {
                    min = dt;
                    minidx = k;
                }
            }
            Color c;
            if (minidx >= 0) {
                Solid* s = solids_[minidx];
                Point surf = p + d * min;
                Line norm = s->get_normal(surf);
                TexPixel tp = s->get_tex(surf);
                for (auto l : lights_) {
                    Vector ldir = (l->pos() - surf).normalized();
                    float lum = tp.kd * (norm.d * ldir);
                    c.r = (float)tp.ka.r * lum;
                    c.g = (float)tp.ka.g * lum;
                    c.b = (float)tp.ka.b * lum;
                }
            }
            img.set_pix(i, j, c);
        }
    }
    return img;
}
