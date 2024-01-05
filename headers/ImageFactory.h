//
// Created by egbor on 2024-01-02.
//

#ifndef IMAGECONTAINER_H
#define IMAGECONTAINER_H
#include <memory>
#include <string>
#include <vector>

using image_pairs = std::pair<std::string, std::vector<std::string>>;
using Image_t = void *;


class ImageFactory {
public:
    /**
     * \brief Stores Images data and performes operations on them
     * \param images_info List of image_info to create a list of images
     */
    explicit ImageFactory(const std::vector<image_pairs>& images_info)
        : image_container(new std::vector<Image_t>()) {
        for (const auto& image_pair: images_info) {
            image_container->push_back(create_image(&image_pair));
        }
    }

    ~ImageFactory() { delete image_container; }

private:
    std::vector<Image_t>* image_container;

    static Image_t create_image(const image_pairs* images_info);
};

#endif //IMAGECONTAINER_H
