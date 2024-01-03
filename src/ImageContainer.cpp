//
// Created by egbor on 2024-01-02.
//

#include "../Header/ImageContainer.h"
#include <string>
#include <sstream>
#include <iostream>

#include <fstream>


// Function to convert a hexadecimal string to bytes
std::string hexStringToBytes(const std::string& hexString) {
    std::stringstream ss;
    for (size_t i = 0; i < hexString.length(); i += 2) {
        std::string byteString = hexString.substr(i, 2);
        const char byte = static_cast<char>(strtol(byteString.c_str(), nullptr, 16));
        ss << byte;
    }
    return ss.str();
}

void view_pixel_data() {
    // Example PNG pixel data in hexadecimal format
    const std::string pngPixelDataHex = "FFFFFFFF0000FF00"; // Replace with your PNG pixel data

    // Convert the hexadecimal string to bytes
    const std::string pngPixelDataBytes = hexStringToBytes(pngPixelDataHex);

    // Assuming the PNG uses 3 channels (RGB), 1 byte per channel
    constexpr int pixelIndex = 0; // Choose the pixel index (0, 1, 2, etc.)
    constexpr int channels = 3; // Number of color channels (R, G, B)
    constexpr int pixelSize = channels; // Assuming 1 byte per channel (RGB)

    // Calculate the offset to access pixel data
    constexpr int offset = pixelIndex * pixelSize;

    // Access color channels for the chosen pixel
    if (offset + channels <= pngPixelDataBytes.size()) {
        int red = static_cast<unsigned char>(pngPixelDataBytes[offset]);
        int green = static_cast<unsigned char>(pngPixelDataBytes[offset + 1]);
        int blue = static_cast<unsigned char>(pngPixelDataBytes[offset + 2]);

        std::cout << "Pixel " << pixelIndex << " - R: " << red << ", G: " << green << ", B: " << blue << std::endl;
    } else {
        std::cout << "Pixel index out of range or incomplete pixel data." << std::endl;
    }
}
