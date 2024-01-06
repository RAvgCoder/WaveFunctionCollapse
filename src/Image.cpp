//
// Created by egbor on 2024-01-06.
//

#include <string>
#include <vector>
#include <iostream>
#include "../headers/Image.h"

Image::Image(std::string file_name, const std::vector<std::vector<int> *>& conectors)
    : file_name(std::move(file_name)), conectors(conectors) {
}

std::string Image::getFileName() const {
    return file_name;
}

void Image::display() const {
    std::cout << "Name: \"" << file_name << "\" {\n\t";
    const std::string directions[] = {"TOP", "BOTTOM", "LEFT", "RIGHT"};
    for (int i = 0; i < conectors.size(); i++) {
        // Makes the image display in its current state of rotation
        const int idx = (i + rotation_idx) % 4;
        const auto pixel_vector = conectors[idx];
        std::cout << "\t" << directions[idx] << ": [ ";
        for (const int pixel: *pixel_vector) {
            std::cout << pixel << " ";
        }
        std::cout << ((idx != 3) ? "]\n" : "]");
    }
    std::cout << "\n}\n" << std::endl;
}

void Image::rotate(const char direction) {
    switch (direction) {
        case 'L':
        case 'l':
            // Rotates the image left
            rotation_idx = static_cast<SIDE>((rotation_idx - 1 + 4) % 4);
            break;
        case 'R':
        case 'r':
            // Rotates the image right
            rotation_idx = static_cast<SIDE>((rotation_idx + 1) % 4);
            break;
        default:
            std::cout << "Cannot rotate in direction=" << direction;
            break;
    }
}

void Image::set_rotation(const SIDE new_top) {
    rotation_idx = new_top;
}

const std::vector<std::vector<int> *>& Image::getConnectors() const {
    return conectors;
}

Image::~Image() {
    for (const auto connector: conectors) {
        delete connector;
    }
    conectors.clear();
}