//
// Created by egbor on 2024-01-02.
//

#ifndef IMAGECONTAINER_H
#define IMAGECONTAINER_H
#include "../headers/Image.h"
#include <memory>
#include <string>
#include <vector>


/**
 * \brief Represents a pair of image file name and its connections.
 */
using image_pairs = std::pair<std::string, std::vector<std::string>>;


/**
 * \brief Factory class for managing Image objects.
 */
class ImageFactory {
public:
    /**
     * \brief Constructs an ImageFactory object.
     * \param images_info List of image_info to create a list of images.
     */
    explicit ImageFactory(const std::vector<image_pairs>& images_info);

    /**
     * \brief Show all images in the container
     */
    void display() const;

    /**
     * \brief Retrieves the number of images in the container.
     * \return The size of the image container.
     */
    [[nodiscard]] unsigned long long container_size() const;

    /**
     * \brief Destroys the ImageFactory object.
     */
    ~ImageFactory();

private:
    // Container for Image objects.
    const std::vector<const Image *>* image_container{};

    /**
     * \brief Creates an Image object from image info.
     * \param images_info Pointer to image info.
     * \return The created Image object.
     */
    static Image* create_image(const image_pairs* images_info);
};

#endif //IMAGECONTAINER_H
