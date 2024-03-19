#include "PNGFormat.h"
#include <fstream>
#include <stdexcept>
#include <png.h>

bool PNGFormat::load(const std::string& filename) {
    FILE *fp = fopen(filename.c_str(), "rb");
    if (!fp) return false;

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png) {
        fclose(fp);
        return false;
    }

    png_infop info = png_create_info_struct(png);
    if (!info) {
        png_destroy_read_struct(&png, nullptr, nullptr);
        fclose(fp);
        return false;
    }

    if (setjmp(png_jmpbuf(png))) {
        png_destroy_read_struct(&png, &info, nullptr);
        fclose(fp);
        return false;
    }

    png_init_io(png, fp);
    png_read_info(png, info);

    width = png_get_image_width(png, info);
    height = png_get_image_height(png, info);
    png_byte color_type = png_get_color_type(png, info);
    png_byte bit_depth = png_get_bit_depth(png, info);

    // Handle PNG color types here. For simplicity, this example assumes PNG_COLOR_TYPE_RGB.
    // You would need to adjust this based on the color_type and bit_depth for a robust loader.

    int number_of_passes = png_set_interlace_handling(png);
    png_read_update_info(png, info);

    // Read file
    if (setjmp(png_jmpbuf(png))) {
        fclose(fp);
        png_destroy_read_struct(&png, &info, nullptr);
        return false;
    }

    png_bytep* row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    for (int y = 0; y < height; y++) {
        row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png, info));
    }

    png_read_image(png, row_pointers);

    // Store pixel values
    pixelValues.clear();
    for (int y = 0; y < height; y++) {
        png_byte* row = row_pointers[y];
        for (int x = 0; x < width; x++) {
            png_byte* ptr = &(row[x * 3]); // Assuming RGB for simplicity
            pixelValues.push_back(ptr[0]); // R
            pixelValues.push_back(ptr[1]); // G
            pixelValues.push_back(ptr[2]); // B
        }
    }

    for (int y = 0; y < height; y++) {
        free(row_pointers[y]);
    }
    free(row_pointers);

    fclose(fp);
    png_destroy_read_struct(&png, &info, nullptr);
    return true;
}

std::string PNGImageLoader::getMetadata() const {
    std::string metadata = "Width: " + std::to_string(width) + "\n";
    metadata += "Height: " + std::to_string(height) + "\n";
    // Add more metadata fields as needed
    return metadata;
}
