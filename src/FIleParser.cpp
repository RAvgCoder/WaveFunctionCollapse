#include <iostream>

#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <vector>

#include "../headers/FileParser.h"
#include "../headers/ImageFactory.h"

static std::vector<image_pairs>* read_from_file();

static std::string trim(const std::string& str);

std::unique_ptr<ImageFactory> create_image_factory() {
    const auto lines = read_from_file();
    return std::make_unique<ImageFactory>(*lines);
}

// Function to trim leading and trailing whitespace from a string
std::string trim(const std::string& str) {
    size_t start = 0;
    size_t end = str.length();

    // Find the start index of non-whitespace characters
    while (start < end && std::isspace(str[start])) {
        start++;
    }

    // Find the end index of non-whitespace characters
    while (end > start && std::isspace(str[end - 1])) {
        end--;
    }

    return str.substr(start, end - start);
}

std::vector<image_pairs>* read_from_file() {
    // File path
    const std::string IMAGE_DATE_FILE = R"(C:\Users\egbor\CLionProjects\WaveFunctionCollapse\resources\output)";

    // Open the file 
    std::ifstream file(IMAGE_DATE_FILE);
    if (!file.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        exit(404);
    }

    const auto lines = new std::vector<image_pairs>();

    std::string line;

    // Check if an error occoured when reading images
    std::getline(file, line);
    line = trim(line);
    if (line.length() > 1) {
        std::cerr << "Error occoured when processing the image {\n" << "\t" << line << "\n}" << std::endl;
        exit(1);
    }

    // If no err then parse the file
    int image_group_counter = 0;
    std::vector<std::string> edge_lines = {};
    while (std::getline(file, line)) {
        line = trim(line); // Removes Leading
        if (std::isalnum(line.substr(0, 1)[0])) {
            image_group_counter++;
            edge_lines.push_back(line);

            // When the image and its connectors have been read process them
            if (image_group_counter == 5) {
                image_pairs pair;
                pair.first = edge_lines.at(0);

                const std::vector subVec(edge_lines.begin() + 1, edge_lines.begin() + 5);
                pair.second = subVec;
                lines->push_back(pair);

                image_group_counter = 0;
                edge_lines.clear();
            }
        }
    }

    return lines;
}
