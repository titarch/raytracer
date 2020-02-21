#include <iostream>
#include "Vector.h"
#include "Image.h"
#include "Scene.h"

int main() {
    Camera cam(Point::back() * 7, Vector::forward(), Vector::up(), 1, 1, 0.1);
    Scene scene(cam);
    UniTex tex(Color(255, 0, 200), 0.7, 0.8, 5);
    Sphere sph(Point::forward(), tex,  1);
    UniTex tex2(Color(0, 255, 200), 0.7, 0.8, 5);
    Sphere sph2(Point::left() + Point::back() * 2, tex2,  0.7);
    UniTex tex3(Color(255, 200, 20), 0.5, 0.5, 3);
    Sphere sph3(Point::left() * 2.5 + Point:: back() * 1.5, tex3, 0.3);
    scene.add_solid(&sph);
    scene.add_solid(&sph2);
    scene.add_solid(&sph3);
    PointLight light(Vector::back() + Vector::left() * 10 + Vector::up() * 2);
    scene.add_light(&light);
//    PointLight light2(Vector::back() * 2 + Vector::right() * 10 + Vector::up() *  2);
//    scene.add_light(&light2);
//    Image img = scene.render(1000, 1000);
//    img.save_ppm("test.ppm");

    scene.render_rt(512, 512);
    return 0;
}
