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
#include "../objects/solids/Triangle.h"
#include "../objects/lights/PointLight.h"

Scene::Scene(camera_ptr cam) : cam_(std::move(cam)), solids_(), lights_() {
    w_ = cam_->width();
    h_ = cam_->height();
    update_view();
}

void Scene::update_view() {
    double zmin = cam_->getZmin();
    const Point& pos = cam_->getPos();
    const Vector& fw = cam_->forward();

    center_ = pos + fw * zmin;
    tl_ = center_ + (w_ / 2) * cam_->left() + (h_ / 2) * cam_->up();
}

Intersection Scene::cast_ray(const Line& ray) {
    return ray::cast_ray(solids_, ray);
}

Vector Scene::get_light_value(Intersection const& its, Line const& ray, int rec_lvl) {
    if (its.d == -1)
        return Vector::zero();

    Point p = ray.o + ray.d * its.d;
    TexPixel const& tp = its.s->get_tex(p);
    Line const& norm = its.s->get_normal(p);
    Vector reflection = ray.d - 2 * (ray.d * norm.d) * norm.d;
    Vector lum = tp.ka.to_vect() * 0.1;
    for (auto const& l : lights_) {
        Vector l_dir = (l->pos() - p).normalized();
        Intersection const& lits = cast_ray({p, l_dir});
        if (lits.d != -1 && lits.d * lits.d < (l->pos() - p).sqrMagnitude())
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
                    tl_ + ((double) i * h_ / height) * cam_->down() + ((double) j * w_ / width) * cam_->right();
            Vector ray_dir = (z_target - cam_->getPos()).normalized();
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
                        cam_->move(cam_->forward());
                        break;
                    case sf::Keyboard::A :
                        cam_->move(cam_->left());
                        break;
                    case sf::Keyboard::S :
                        cam_->move(cam_->back());
                        break;
                    case sf::Keyboard::D :
                        cam_->move(cam_->right());
                        break;
                    case sf::Keyboard::LShift:
                        cam_->move(cam_->up());
                        break;
                    case sf::Keyboard::LControl:
                        cam_->move(cam_->down());
                        break;
                    case sf::Keyboard::I :
                        cam_->rotate(0, -.1, 0);
                        break;
                    case sf::Keyboard::J :
                        cam_->rotate(-.1, 0, 0);
                        break;
                    case sf::Keyboard::K :
                        cam_->rotate(0, .1, 0);
                        break;
                    case sf::Keyboard::L :
                        cam_->rotate(.1, 0, 0);
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
                        tl_ + ((double) i * h_ / height) * cam_->down() + ((double) j * w_ / width) * cam_->right();
                Vector ray_dir = (z_target - cam_->getPos()).normalized();
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

Scene Scene::load(const std::string& path) {
    static texmat_ptr default_tex = std::make_shared<UniTex>(Color(255, 255, 255), 0.5, 0.5, 5);
    YAML::Node node = YAML::LoadFile(path);

    camera_ptr cam;
    if (node["camera"]) {
        const auto& camera = node["camera"];
        auto origin = camera["origin"].as<Vector>();
        auto forward = camera["forward"].as<Vector>();
        auto up = camera["up"].as<Vector>();
        auto x = camera["x"] ? camera["x"].as<double>() : M_PI / 2;
        auto y = camera["y"] ? camera["y"].as<double>() : atanf(16.f / 9);
        auto zmin = camera["zmin"] ? camera["zmin"].as<double>() : 0.05;
        cam = std::make_unique<Camera>(origin, forward, up, x, y, zmin);
    } else
        cam = std::make_unique<Camera>(Point::back() * 7, Point::forward(), Point::up(), M_PI / 2, atanf(16.f / 9), 0.05);

    Scene scene(std::move(cam));
    const auto& textures = node["textures"];
    texmats texs;
    for (const auto& texture : textures) {
        texmat_ptr tex;
        if (texture["type"].as<std::string>() == "uni") {
            auto r = texture["r"].as<unsigned>();
            auto g = texture["g"].as<unsigned>();
            auto b = texture["b"].as<unsigned>();
            auto kd = texture["kd"].as<double>();
            auto ks = texture["ks"].as<double>();
            auto ns = texture["ns"].as<double>();
            tex = std::make_shared<UniTex>(Color(r, g, b), kd, ks, ns);
        }
        texs.push_back(std::move(tex));
    }

    const auto& solids = node["objects"]["solids"];
    for (const auto& solid : solids) {
        auto type = solid["type"].as<std::string>();
        auto tex_idx = solid["tex"] ? solid["tex"].as<int>() : -1;
        auto tex = tex_idx >= 0 ? texs[tex_idx % texs.size()] : default_tex;
        solid_ptr s;
        if (type == "cylinder") {
            auto base = solid["base"].as<Vector>();
            auto axis = solid["axis"].as<Vector>();
            auto radius = solid["radius"].as<double>();
            s = std::make_unique<Cylinder>(base, tex, axis, radius);
        } else if (type == "sphere") {
            auto origin = solid["origin"].as<Vector>();
            auto radius = solid["radius"].as<double>();
            s = std::make_unique<Sphere>(origin, tex, radius);
        } else if (type == "triangle") {
            auto v0 = solid["v0"].as<Point>();
            auto v1 = solid["v1"].as<Point>();
            auto v2 = solid["v2"].as<Point>();
            s = std::make_unique<Triangle>(tex, v0, v1, v2);
        }
        if (!s)
            throw std::invalid_argument(std::string("Unrecognized solid type: ") + type);
        scene.solids_.push_back(std::move(s));
    }

    if (node["objects"]["lights"]) {
        const auto& lights = node["objects"]["lights"];
        for (const auto& light : lights) {
            auto type = light["type"].as<std::string>();
            light_ptr l;
            if (type == "point") {
                auto origin = light["origin"].as<Point>();
                l = std::make_unique<PointLight>(origin);
            }
            if (!l)
                throw std::invalid_argument(std::string("Unrecognized light type: ") + type);
            scene.lights_.push_back(std::move(l));
        }
    }

    return scene;
}

