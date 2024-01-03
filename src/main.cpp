#include <iostream>

#include <string>
#include <sstream>
#include <fstream>

#include "../Header/FileHandler.h"
#include "../Header/ImageContainer.h"


int main() {
    openFile("resources/tile_down.png");
    view_pixel_data();

    return 0;
}
