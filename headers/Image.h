//
// Created by egbor on 2024-01-06.
//

#ifndef IMAGE_H
#define IMAGE_H
#include <string>
#include <vector>

typedef enum {
    TOP = 0,
    BOTTOM = 1,
    LEFT = 2,
    RIGHT = 3,
} SIDE;

/**
 * \brief Represents an image with a file name and connections.
 */
class Image {
public:
    /**
      * \brief Constructs an Image object.
      * \param file_name The name of the image file.
      * \param conectors A vector of connections within the image.
      */
    Image(std::string file_name, const std::vector<std::vector<int> *>& conectors);

    /**
     * \brief Function to get the file name
     * \return The name of the file the image is found in
     */
    [[nodiscard]] std::string getFileName() const;

    /**
     * \brief Dispalys the name and properties of the image
     * Name: "name" {
     *     TOP: [ NUMS ]
     *     BOTTOM: [ NUMS ]
     *     LEFT: [ NUMS ]
     *     RIGHT: [ NUMS ]
     * }
     */
    void display() const;

    /**
      * \brief Rotate the image in a particular direction
      * \param direction Direction to rotate the image
      */
    void rotate(char direction);

    /**
      * \brief Sets a new rotation for the image with respect to the top side.
      * \param new_top The new rotation direction to set.
      *        Should be one of the enum values: TOP, BOTTOM, LEFT, RIGHT.
      */
    void set_rotation(SIDE new_top);

    // Gets the connectors for an image
    [[nodiscard]] const std::vector<std::vector<int> *>& getConnectors() const;

    /**
      * \brief Destroys the Image object.
      */
    ~Image();

private:
    std::string file_name;
    std::vector<std::vector<int> *> conectors;
    // Used to track the rotaiton of the image
    SIDE rotation_idx = TOP;
};


#endif //IMAGE_H
