#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "../headers/FileParser.h"
#include "../headers/ImageFactory.h"

void load_images(std::string absolute_path);

int main() {
    std::cout << "Input the absolute file path to the image" << std::endl;
    // C:\\Users\\egbor\\CLionProjects\\WaveFunctionCollapse\\resources

    std::string absolute_path;
    std::cin >> absolute_path;

    load_images(absolute_path);

    const std::unique_ptr<ImageFactory> image_factory = create_image_factory();

    image_factory->display();

    return 0;
}

void load_images(std::string absolute_path) {
    // Python
    std::string python_cmd_runner;
    const std::string PYTHON_EXE = R"(python C:\Users\egbor\CLionProjects\WaveFunctionCollapse\src\ImageLoader.py)";

    // python_cmd_runner = PYTHON_EXE + " " + absolute_path;
    python_cmd_runner = PYTHON_EXE + " " + R"(C:\\Users\\egbor\\CLionProjects\\WaveFunctionCollapse\\resources)";

    const char* exe = python_cmd_runner.c_str();

    system(exe);
}
