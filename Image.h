//
// Created by parsy_b on 2/12/20.
//

#ifndef RAYTRACER_IMAGE_H
#define RAYTRACER_IMAGE_H

#include <string>
#include "Color.h"

class Image {
public:
    Image(unsigned w, unsigned h) : w_(w), h_(h) {
        pixels_ = new Color*[h];
        for (auto i = 0u; i < h; ++i)
            pixels_[i] = new Color[w];
    }

    ~Image() {
        for (unsigned i = 0; i < h_; ++i)
            delete[] pixels_[i];
        delete[] pixels_;
    }

    void save_ppm(std::string const& path);
    void save_now();
    void test();

    void set_pix(unsigned int i, unsigned int i1, Color color);

private:
    unsigned w_, h_;
    Color **pixels_;
};


#endif //RAYTRACER_IMAGE_H
