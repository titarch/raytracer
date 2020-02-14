#include <iostream>
#include "Vector.h"
#include "Image.h"
#include "Scene.h"

int main() {
    Camera cam(Vector::back() * 5, Vector::zero(), 1, 1, 1);
    Scene scene(cam);
    UniTex tex(Color(255, 0, 200), 0.5, 0.5, 0.5);
    Sphere sph(Point::zero(), tex,  1);
    UniTex tex2(Color(0, 255, 200), 0.5, 0.5, 0.5);
    Sphere sph2(Point::left() + Point::back() * 2, tex2,  0.7);
    scene.add_solid(&sph);
    scene.add_solid(&sph2);
    PointLight light(Vector::back() * 7 + Vector::left() * 8 + Vector::up() * 3);
    scene.add_light(&light);
    Image img = scene.render(1000, 1000);
    img.save_ppm("test.ppm");
    return 0;
}
