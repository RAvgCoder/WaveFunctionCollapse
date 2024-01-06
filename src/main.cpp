#include <iostream>

#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "../headers/FileParser.h"
#include "../headers/ImageFactory.h"


int main() {
    std::cout << "Input the absolute file path to the image" << std::endl;
    // C:\\Users\\egbor\\CLionProjects\\WaveFunctionCollapse\\resources

    std::string absolute_path;
    std::cin >> absolute_path;

    const std::unique_ptr<ImageFactory> image_factory = processImages(absolute_path);

    image_factory->display();


    return 0;
}
