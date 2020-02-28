#include <iostream>
#include "Vector.h"
#include "Image.h"
#include "Scene.h"

int main() {
    Camera cam(Point::back() * 7, Vector::forward(), Vector::up(), M_PI / 2, atanf(16.f / 9), 0.05);
//    cam.rotate(0, -M_PI / 2 + 0.4, 0);
    Scene scene(cam);
    UniTex tex(Color(255, 0, 200), 0.5, 0.5, 5);
    Sphere sph(Point::forward(), tex, 1);
    UniTex tex2(Color(0, 255, 200), 0.5, 0.5, 4);
    Sphere sph2(Point::left() + Point::back() * 2, tex2, 0.7);
    UniTex tex3(Color(255, 200, 20), 0.5, 0.5, 3);
    Sphere sph3(Point::left() * 2.2 + Point::back() * 2.3 + Point::up() * 0.2, tex3, 0.3);
    scene.add_solid(&sph);
    scene.add_solid(&sph2);
    scene.add_solid(&sph3);

    UniTex tex4(Color(0, 32, 255), 1, 0.1, 1);
    Plane plane(Point::down(), tex4, Vector::up());
    Plane plane2(Point::up() * 4, tex4, Vector::down());
    scene.add_solid(&plane);
//    scene.add_solid(&plane2);

    PointLight light(Vector::back() * 2 + Vector::left() * 10 + Vector::up() * 2);
    scene.add_light(&light);
//    PointLight light2(Vector::back() * 2 + Vector::right() * 10 + Vector::up() *  2);
//    scene.add_light(&light2);
//    Image img = scene.render(1000, 1000);
//    img.save_ppm("test.ppm");

    scene.render_rt(1920, 1080);
    return 0;
}
