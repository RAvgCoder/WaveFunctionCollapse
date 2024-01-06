//
// Created by egbor on 2024-01-02.
//

#include "../headers/ImageFactory.h"

#include <iostream>
#include <string>
#include <sstream>
#include <utility>

// Constructor for ImageFactory
ImageFactory::ImageFactory(const std::vector<image_pairs>& images_info) {
    const auto images = new std::vector<const Image *>();
    for (const auto& image_pair: images_info) {
        images->push_back(create_image(&image_pair));
    }
    image_container = images;
}

// Retrieves the number of images in the container
unsigned long long ImageFactory::container_size() const {
    return image_container->size();
}

// Creates an Image object from image info
Image* ImageFactory::create_image(const image_pairs* images_info) {
    const auto image_connectors = new std::vector<std::vector<int> *>();

    // Process each list of raw string connectors to list of int connectors
    for (const auto& current_connector: images_info->second) {
        // Parse the connectors to an int "1 2 3" -> [1, 2, 3]
        const auto connector = new std::vector<int>();
        // Read the connector as a stream
        std::istringstream number_stream(current_connector);
        std::string number;

        // Convert each num from a string into its decimal form
        while (std::getline(number_stream, number, ' ')) {
            connector->push_back(std::stoi(number));
        }

        // Add the parsed number stream to the connectors
        image_connectors->push_back(connector);
    }

    return new Image(images_info->first, *image_connectors);;
}

// Displays information about the images in the container
void ImageFactory::display() const {
    for (const auto image: *image_container) {
        image->display();
    }
}

// Destructor for ImageFactory
ImageFactory::~ImageFactory() {
    for (const auto image: *image_container) {
        // Delete each vector pointed to by the pointers in image_container
        delete image;
    }
    delete image_container; // Delete the vector of pointers itself
    image_container = nullptr; // Set the pointer to null to avoid dangling pointer
}
