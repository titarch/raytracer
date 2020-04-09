#include <iostream>
#include "utils/Vector.h"
#include "engine/Camera.h"
#include "engine/Scene.h"
#include "objects/textures/UniTex.h"
#include "objects/solids/Sphere.h"
#include "objects/solids/Plane.h"
#include "objects/lights/PointLight.h"
#include "engine/Blob.h"
#include "objects/solids/Cylinder.h"

int main() {
    Camera cam(Point::back() * 7, Vector::forward(), Vector::up(), M_PI / 2, atanf(16.f / 9), 0.05);
//    Camera cam(Point::forward() * 30 + Point::up() * 60 + Point::left() * 15, Vector::down(), Vector::right(), M_PI / 2, atanf(16.f / 9), 0.05);
//    cam.rotate(0, -M_PI / 2 + 0.4, 0);

    Scene scene(std::make_unique<Camera>(cam));
    auto tex = std::make_shared<UniTex>(Color(255, 0, 200), 0.5, 0.5, 5);
    auto tex2 = std::make_shared<UniTex>(Color(0, 255, 200), 0.5, 0.5, 4);
    auto tex3 = std::make_shared<UniTex>(Color(255, 200, 20), 0.5, 0.5, 3);
    auto tex4 = std::make_shared<UniTex>(Color(0, 32, 255), 1, 0.1, 1);

    Sphere sph(Point::forward(), tex, 1);
    Sphere sph2(Point::left() + Point::back() * 2, tex2, 0.7);
    Sphere sph3(Point::left() * 2.2 + Point::back() * 2.3 + Point::up() * 0.2, tex3, 0.3);
    Plane plane(Point::down() * 2, tex4, Vector::up());
    PointLight light(Vector::back() * 2 + Vector::left() * 10 + Vector::up() * 2);

    scene
        .push_solid(sph)
        .push_solid(sph2)
        .push_solid(sph3)
        .push_solid(plane)
        .push_light(light);

//    Blob blob({
//                      ChargedPoint{Point{-1.5, 0, 3}, 1.01},
//                      ChargedPoint{Point{1.5, 0, 3}, 1.02}
//              }, Blob::pf_square, {
//                      Point{-3, -3, 0}, 6
//              }, 0.5, 0.5);
//    blob.render(scene, tex);

//    scene.load("objs.yaml");
    scene.render_rt(1920, 1080);
    return 0;
}
