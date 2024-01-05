//
// Created by egbor on 2024-01-02.
//

#include "../headers/ImageFactory.h"
#include <string>
#include <sstream>

typedef struct Image {
    std::string file_name;
    std::vector<std::vector<int> *> conectors;
} Image;

Image_t ImageFactory::create_image(const image_pairs* images_info) {
    const auto image_connectors = new std::vector<std::vector<int> *>();

    // Process each list of raw string connectors to list of int connectors
    for (const auto& current_connector: images_info->second) {
        // Parse the connectors to an int "1 2 3" -> [1, 2, 3]
        const auto connector = new std::vector<int>();
        // Read the connector as a stream
        std::istringstream conector_stream(current_connector);
        std::string token;

        while (std::getline(conector_stream, token, ' ')) {
            connector->push_back(std::stoi(token));
        }

        image_connectors->push_back(connector);
        connector->clear();
    }

    auto* image = new Image();
    image->file_name = images_info->first;
    image->conectors = *image_connectors;
    return image;
}
