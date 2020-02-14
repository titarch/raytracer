//
// Created by parsy_b on 2/12/20.
//

#include <fstream>
#include "Image.h"

void Image::save_ppm(const std::string& path) {
    auto file = std::fstream(path, std::ios::out | std::ios::binary);
    file << "P6 " << w_ << ' ' << h_ << " 255\n";
    for (auto i = 0u; i < h_; ++i) {
        for (auto j = 0u; j < w_; ++j) {
            file.write((char *) &pixels_[i][j].r, 1);
            file.write((char *) &pixels_[i][j].g, 1);
            file.write((char *) &pixels_[i][j].b, 1);
        }
    }
}

void Image::test() {
    for (auto i = 0u; i < h_; ++i) {
        for (auto j = 0u; j < w_; ++j) {
            pixels_[i][j].r = i;
            pixels_[i][j].g = j;
            pixels_[i][j].b = (256 + i - j) % 256;
        }
    }
}

void Image::set_pix(unsigned int i, unsigned int j, Color color) {
    pixels_[i][j] = color;
}
