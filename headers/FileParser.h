//
// Created by egbor on 2024-01-02.
//

#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include "ImageFactory.h"
using image_pairs = std::pair<std::string, std::vector<std::string>>;

std::unique_ptr<ImageFactory> create_image_factory();

#endif //FILEHANDLER_H
