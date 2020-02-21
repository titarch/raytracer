//
// Created by parsy_b on 2/12/20.
//

#include "Scene.h"
#include <SFML/Graphics.hpp>

Scene::Scene(Camera& cam) : cam_(cam), solids_(), lights_() {
    w_ = cam.width();
    h_ = cam.height();
    update_view();
}

void Scene::update_view() {
    float zmin = cam_.getZmin();
    const Point& pos = cam_.getPos();
    const Vector& fw = cam_.forward();

    center_ = pos + fw * zmin;
    tl_ = center_ + (w_ / 2) * cam_.left() + (h_ / 2) * cam_.up();
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
    Vector lum = tp.ka.to_vect() * 0.03;
    for (auto l : lights_) {
        Vector l_dir = (l->pos() - p).normalized();
        Intersection lits = cast_ray({p, l_dir});
        if (lits.s != nullptr && lits.d * lits.d < (l->pos() - p).sqrMagnitude())
            continue;
        Vector local_lum = tp.kd * tp.ka.to_vect() * (norm.d * l_dir) +
                           tp.ks * Vector::one() * std::pow((-reflection * l_dir), tp.ns);
        lum += local_lum;
    }
    return Color::from_vect(lum);
}

Image Scene::render(unsigned int width, unsigned int height) {
    Image img = Image(width, height);

    for (auto i = 0u; i < height; ++i) {
        for (auto j = 0u; j < width; ++j) {
            Point z_target =
                    tl_ + ((float) i * h_ / height) * cam_.down() + ((float) j * w_ / width) * cam_.right();
            Vector ray_dir = (z_target - cam_.getPos()).normalized();
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

void Scene::render_rt(unsigned int width, unsigned int height) {
    sf::RenderWindow window(sf::VideoMode(width, height), "sfml");
    auto *pixels = new sf::Uint8[width * height * 4];
    sf::Image img;
    sf::Texture stex;
    sf::Sprite sprite;

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::W :
                        cam_.move(cam_.forward());
                        break;
                    case sf::Keyboard::A :
                        cam_.move(cam_.left());
                        break;
                    case sf::Keyboard::S :
                        cam_.move(cam_.back());
                        break;
                    case sf::Keyboard::D :
                        cam_.move(cam_.right());
                        break;
                    case sf::Keyboard::I :
                        cam_.rotate(0, .1, 0);
                        break;
                    case sf::Keyboard::J :
                        cam_.rotate(-.1, 0, 0);
                        break;
                    case sf::Keyboard::K :
                        cam_.rotate(0, -.1, 0);
                        break;
                    case sf::Keyboard::L :
                        cam_.rotate(.1, 0, 0);
                        break;
                    default:
                        break;
                }
                update_view();
            }
        }


        auto *px = pixels;

        for (auto i = 0u; i < height; ++i) {
            for (auto j = 0u; j < width; ++j) {
                Point z_target =
                        tl_ + ((float) i * h_ / height) * cam_.down() + ((float) j * w_ / width) * cam_.right();
                Vector ray_dir = (z_target - cam_.getPos()).normalized();
                Line ray = {z_target, ray_dir};
                Intersection its = cast_ray(ray);

                Color c;
                if (its.s != nullptr)
                    c = get_light_value(its, ray);
                *px++ = c.r;
                *px++ = c.g;
                *px++ = c.b;
                *px++ = 255;
            }
        }

        img.create(width, height, pixels);
        stex.loadFromImage(img);
        sprite.setTexture(stex);

        window.clear();
        window.draw(sprite);
        window.display();
    }

    delete[] pixels;
}
