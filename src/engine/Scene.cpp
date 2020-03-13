//
// Created by parsy_b on 2/12/20.
//

#include "Scene.h"
#include <SFML/Graphics.hpp>
#include <yaml-cpp/yaml.h>
#include "convert.h"
#include <iostream>
#include "ray.h"
#include "../objects/solids/Cylinder.h"
#include "../objects/textures/UniTex.h"
#include "../objects/solids/Sphere.h"

Scene::Scene(Camera& cam) : cam_(cam), solids_(), lights_() {
    w_ = cam.width();
    h_ = cam.height();
    update_view();
}

void Scene::update_view() {
    double zmin = cam_.getZmin();
    const Point& pos = cam_.getPos();
    const Vector& fw = cam_.forward();

    center_ = pos + fw * zmin;
    tl_ = center_ + (w_ / 2) * cam_.left() + (h_ / 2) * cam_.up();
}

void Scene::add_solid(Solid* s) {
    solids_.push_back(s);
}

void Scene::add_light(Light* l) {
    lights_.push_back(l);
}

Intersection Scene::cast_ray(const Line& ray) {
    return ray::cast_ray(solids_, ray);
}

Vector Scene::get_light_value(Intersection const& its, Line const& ray, int rec_lvl) {
    if (its.s == nullptr)
        return Vector::zero();

    Point p = ray.o + ray.d * its.d;
    TexPixel const& tp = its.s->get_tex(p);
    Line const& norm = its.s->get_normal(p);
    Vector reflection = ray.d - 2 * (ray.d * norm.d) * norm.d;
    Vector lum = tp.ka.to_vect() * 0.1;
    for (auto l : lights_) {
        Vector l_dir = (l->pos() - p).normalized();
        Intersection const& lits = cast_ray({p, l_dir});
        if (lits.s != nullptr && lits.d * lits.d < (l->pos() - p).sqrMagnitude())
            continue;
        Vector local_lum = tp.kd * tp.ka.to_vect() * std::clamp(norm.d * l_dir, 0.0, Inf) +
                           tp.ks * Vector::one() * std::pow(std::clamp(reflection * l_dir, 0.0, Inf), tp.ns);
        lum += local_lum;
    }

    if (rec_lvl >= REFLECTION_REC_LVL_MAX)
        return lum;

    Line reflection_ray(p, reflection);
    Intersection const& rits = cast_ray(reflection_ray);
    return lum + tp.kd * get_light_value(rits, reflection_ray, rec_lvl + 1);
}

Image Scene::render(unsigned int width, unsigned int height) {
    Image img = Image(width, height);
    auto i = 0u, j = 0u;

#pragma omp parallel for private(i, j) shared(img) collapse(2)
    for (i = 0u; i < height; ++i) {
        for (j = 0u; j < width; ++j) {
            Point z_target =
                    tl_ + ((double) i * h_ / height) * cam_.down() + ((double) j * w_ / width) * cam_.right();
            Vector ray_dir = (z_target - cam_.getPos()).normalized();
            Line ray = {z_target, ray_dir};
            Intersection its = cast_ray(ray);

            Color c = Color::from_vect(get_light_value(its, ray));
            img.set_pix(i, j, c);
        }
    }
    return img;
}

void Scene::render_rt(unsigned int width, unsigned int height) {
    sf::RenderWindow window(sf::VideoMode(width, height), "sfml-raytracer");
    auto* pixels = new sf::Uint8[width * height * 4];
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
                    case sf::Keyboard::LShift:
                        cam_.move(cam_.up());
                        break;
                    case sf::Keyboard::LControl:
                        cam_.move(cam_.down());
                        break;
                    case sf::Keyboard::I :
                        cam_.rotate(0, -.1, 0);
                        break;
                    case sf::Keyboard::J :
                        cam_.rotate(-.1, 0, 0);
                        break;
                    case sf::Keyboard::K :
                        cam_.rotate(0, .1, 0);
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


        auto* px = pixels;

        unsigned i, j;
#pragma omp parallel for private(i, j) shared(img) collapse(2)
        for (i = 0u; i < height; ++i) {
            for (j = 0u; j < width; ++j) {
                Point z_target =
                        tl_ + ((double) i * h_ / height) * cam_.down() + ((double) j * w_ / width) * cam_.right();
                Vector ray_dir = (z_target - cam_.getPos()).normalized();
                Line ray = {z_target, ray_dir};
                Intersection const& its = cast_ray(ray);

                Color const& c = Color::from_vect(get_light_value(its, ray));
                px[4 * (i * width + j)] = c.r;
                px[4 * (i * width + j) + 1] = c.g;
                px[4 * (i * width + j) + 2] = c.b;
                px[4 * (i * width + j) + 3] = 255;
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

void Scene::load(const char* path) {
    static UniTex default_tex(Color(255, 255, 255), 0.5, 0.5, 5);
    YAML::Node node = YAML::LoadFile(path);


    const auto textures = node["textures"][0];
    std::vector<TexMat*> texs;
    for (const auto& texture : textures) {
        TexMat* tex = nullptr;
        if (texture["type"].as<std::string>() == "uni") {
            auto r = texture["r"].as<uint8_t>();
            auto g = texture["g"].as<uint8_t>();
            auto b = texture["b"].as<uint8_t>();
            auto kd = texture["kd"].as<double>();
            auto ks = texture["ks"].as<double>();
            auto ns = texture["ns"].as<double>();
            tex = new UniTex(Color(r, g, b), kd, ks, ns);
        }
        texs.push_back(tex);
    }

    const auto solids = node["objects"]["solids"][0];
    for (const auto& solid : solids) {
        auto type = solid["type"].as<std::string>();
        Solid* s = nullptr;
        if (type == "cylinder") {
            auto tex_idx = solid["tex"] ? solid["tex"].as<int>() : -1;
            auto* tex = tex_idx >=0 ? texs[tex_idx] : &default_tex;
            auto base = solid["base"].as<Vector>();
            auto axis = solid["axis"].as<Vector>();
            auto radius = solid["radius"].as<double>();
            s = new Cylinder(base, *tex, axis, radius);
        } else if (type == "sphere") {
            auto tex_idx = solid["tex"] ? solid["tex"].as<int>() : -1;
            auto* tex = tex_idx >=0 ? texs[tex_idx] : &default_tex;
            auto origin = solid["origin"].as<Vector>();
            auto radius = solid["radius"].as<double>();
            s = new Sphere(origin, *tex, radius);
        }
        if (s == nullptr)
            throw std::invalid_argument(std::string("Unrcognized solid type: ") + type);
        add_solid(s);
    }
}
