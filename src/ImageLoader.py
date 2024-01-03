import sys
import json
from typing import List, Tuple, Any
from pathlib import Path
from PIL import Image


class ImageProcessor:
    """
    This class is responsible for loading and preparing images from to extract the
    edge pixels from the image
    """
    def __init__(self, directory: Path) -> None:
        self.directory: Path = directory
        self.output_directory: str = str(directory) + "\\output"

    def load_images(self) -> list:
        """
        Load images from a directory and return them as a list of PIL Images
        :return: List of PIL Images
        """
        image_extensions = ['.jpg', '.jpeg', '.png', '.gif', '.bmp', '.svg']
        image_files = list(self.directory.glob('*'))
        image_files = [file for file in image_files if file.suffix.lower() in image_extensions]
        return image_files

    def to_file(self, message: str) -> None:
        with open(self.output_directory, 'w') as file:
            file.write(message)

    def check_condition(self, message: str, condition: bool) -> None:
        if condition:
            self.error(f"Error: {message}")

    def __error(self, message: str) -> None:
        ImageProcessor.to_file(self, message)
        exit(1)

    @staticmethod
    def extract_pixel(image, palette, i: int, j: int) -> int:
        """
        Extract pixel value from a given image and return it as a tuple
        :param image: The image object
        :param palette: The palette for the image
        :param i: The index of the row of pixel to extract
        :param j: The index of the column of pixel to extract
        :return: A tuple containing the pixel value (red, green, blue)
        """
        idx = image.getpixel((i, j))
        base = 3 * idx
        red, green, blue = palette[base:base + 3]
        return (red << 16) + (green << 8) + blue

    @staticmethod
    def get_edges_from_an_image(image) -> list[tuple[str, list[int]]]:
        """
        Extract edges from an image and return them as a list of tuples with the pos and the edge color for each pixel
        :param image: The image object containing the image to extract edges from
        :return: A list of tuples with the pos and the edge color for each pixel
        """
        palette = image.getpalette()
        width, height = image.size
        if width != height:
            return []
        else:
            return [
                ("TOP", [ImageProcessor.extract_pixel(image, palette, i, 0) for i in range(height)]),
                ("BOTTOM", [ImageProcessor.extract_pixel(image, palette, i, width - 1) for i in range(height)]),
                ("LEFT", [ImageProcessor.extract_pixel(image, palette, 0, j) for j in range(width)]),
                ("RIGHT", [ImageProcessor.extract_pixel(image, palette, width - 1, j) for j in range(width)]),
            ]

    @staticmethod
    def get_edges_from_images(images) -> list[list[tuple[str, list[int]]]]:
        return [ImageProcessor.get_edges_from_an_image(Image.open(image)) for image in
                images]


def images_to_string(image_with_edges: list[tuple[str, list[tuple[str, list[int]]]]], directory: Path) -> str:
    """
    Writes the structure if image and edges to a list in this format
    [
        {
            IMAGE_NAME_1: {
                Top: "1 2 3"
                Bottom: "1 2 3"
                LEFT: "1 2 3"
                Right: "1 2 3"
            }
        },
        {
            "IMAGE_NAME_n": {
                Top: "1 2 3"
                Bottom: "1 2 3"
                LEFT: "1 2 3"
                Right: "1 2 3"
            }
        }
    ]
    :param image_with_edges:
    :param directory:
    :return: the structure of the images list in json
    """

    output_data = []

    for image_name, image_info in image_with_edges:
        formatted_data = {
            image_name: {
                image_info[0][0]: ' '.join(map(str, image_info[0][1])),
                image_info[1][0]: ' '.join(map(str, image_info[1][1])),
                image_info[2][0]: ' '.join(map(str, image_info[2][1])),
                image_info[3][0]: ' '.join(map(str, image_info[3][1])),
            }
        }
        output_data.append(formatted_data)

    # Serialize the list of dictionaries to a JSON-formatted string
    json_output: str = json.dumps(output_data, indent=4)  # indent for pretty formatting

    return json_output


def process_directions(edge_dir_with_pixel: list[tuple[str, list[int]]]) -> str:
    return '\n'.join(["""
    %s: %s
    """.strip() % (edge, ' '.join(map(str, pixels))) for edge, pixels in edge_dir_with_pixel])


def main():
    # Check if the file location was provided
    if len(sys.argv) < 2:
        print("Usage: python script.py <absolute_directory_path>")
        return

    directory_path: Path = Path(sys.argv[1])
    image_processor = ImageProcessor(directory_path)
    images = image_processor.load_images()

    # Check if any images were found
    image_processor.check_condition("No images found", len(images) == 0)

    edge_list: list[list[tuple[str, list[int]]]] = ImageProcessor.get_edges_from_images(images)

    # Check if the width and height of the image is the same
    image_processor.check_condition("Width and Height don't match", any(len(edge) == 0 for edge in edge_list))

    # Add the image name with its corresponding edge structure
    image_with_edges: list[tuple[str, list[tuple[str, list[int]]]]] = []
    for i in range(len(images)):
        image_path = str(images[i])
        image_edges = edge_list[i]
        image_with_edges.append((image_path, image_edges))

    image_processor.to_file(images_to_string(image_with_edges, image_processor.directory))


if __name__ == "__main__":
    main()
