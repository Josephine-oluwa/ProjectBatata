#include "VolumeJPEGFormat.h"
#include <stdio.h>
#include <setjmp.h>

bool VolumeJPEGFormat::load(const std::string& filename) {
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE *infile = fopen(filename.c_str(), "rb");
    if (!infile) {
        return false;
    }

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, infile);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);

    width = cinfo.output_width;
    height = cinfo.output_height;

    unsigned long bmp_size = width * height * cinfo.output_components;
    auto* buffer = new unsigned char[bmp_size]; // Allocate buffer for the raw image

    while (cinfo.output_scanline < cinfo.output_height) {
        unsigned char *rowptr[1]; // JPEG read_scanlines expects an array of pointers
        rowptr[0] = &buffer[cinfo.output_scanline * width * cinfo.output_components];
        jpeg_read_scanlines(&cinfo, rowptr, 1);
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(infile);

    // Convert raw buffer to pixelValues
    pixelValues.clear();
    for (unsigned long i = 0; i < bmp_size; i += cinfo.output_components) {
        // Assuming RGB for simplicity, even though JPEG can be grayscale (in which case adjust accordingly)
        pixelValues.push_back(buffer[i]);   // R
        pixelValues.push_back(buffer[i+1]); // G
        pixelValues.push_back(buffer[i+2]); // B
    }

    delete[] buffer;
    return true;
}

std::string VolumeJPEGFormat::getMetadata() const {
    std::string metadata = "Width: " + std::to_string(width) + "\n";
    metadata += "Height: " + std::to_string(height) + "\n";
    metadata += "Color Space: ";
    switch (cinfo.out_color_space) {
        case JCS_GRAYSCALE:
            metadata += "Grayscale";
            break;
        case JCS_RGB:
            metadata += "RGB";
            break;
        case JCS_YCbCr:
            metadata += "YCbCr";
            break;
        case JCS_CMYK:
            metadata += "CMYK";
            break;
        case JCS_YCCK:
            metadata += "YCCK";
            break;
        default:
            metadata += "Unknown";
            break;
    }
    metadata += "\n";
    // Add more metadata fields as needed
    return metadata;
}
