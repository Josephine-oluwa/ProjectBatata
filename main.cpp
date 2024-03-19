#include <iostream>
#include <iostream>
#include <vector>
#include "2D/Headers/ImageProcessor.h"
#include "Volume/Headers/VolumeImageProcessor.h"
#include "STLLoader.h"
/*
    MAIN.CPP
    Usage: program_name <dimensionality> <format> <file(s)>
        - dimensionality: 2D, 3D, or 4D
        - format: DICOM, NIFTI, PNG, JPEG
        - file(s): For 2D, a single file. For 3D/4D, a list of files or a directory.

    Receive user input for 2D 
        "main.cpp 2D DICOM file.dcm"
    Receive user input for 3D
        "main.cpp 3D DICOM file.dcm file.dcm file.dcm"
*/
int main(int argc, char* argv[]) {
    if (argc < 5) {
         std::cerr << "Usage: " << argv[0] << " <dimensionality> <format> <file(s)>" << std::endl;
         return 1;
     };
    std::string dimensionality = argv[1];
    std::string format = argv[2];
    std::vector<std::string> files;
    if (dimensionality == "2D") {
        if (files.size() != 1) {
            std::cerr << "Error: Expected exactly one file for 2D processing." << std::endl;
            return false;
        };
        
        auto create_image_2D = createImageFormat(format);
        if (!create_image_2D) {
            std::cerr << "Failed to create image format object." << std::endl;
            return false;
        };
        auto processedImage_2D = LoadImage(files[0], std::move(create_image_2D));
        if (processedImage_2D) {
            //std::cout << "MetaData: " <<processedImage_2D->getMetadata<< std::endl
            //std::cout << "PixelData: " <<processedImage_2D->getPixelValues<< std::endl
            return true;
        }else {
            std::cerr << "Processing image failed or image format not supported." << std::endl;
        };
    }else if (dimensionality != "2D") {
        if (format == "DICOM" || format == "PNG" || format == "JPEG") {
            if (files.size() <= 1) {
                std::cerr << "Error: Expected multiple files for 3D/4D processing in DICOM/PNG/JPEG format." << std::endl;
                return false;
            };
            // Process each file, assuming createImageFormat and LoadandSaveImage support 3D/4D
            for (const auto& file : files) {
                auto create_image_3D = VolumecreateImageFormat(format);
                if (!create_image_3D) {
                    std::cerr << "Failed to create image format object." << std::endl;
                    return false;
                }
                auto processedImage_3D = VolumeLoadImage(file, std::move(create_image_3D));
                if (processedImage_3D) {
                    //std::cout << "MetaData: " <<processedImage_3D->getMetadata<< std::endl
                    //std::cout << "PixelData: " <<processedImage_3D->getPixelValues<< std::endl

                    return true;
                }else {
                    std::cerr << "Processing image failed or image format not supported." << std::endl;
                };
                // Handle processedImage as needed
            };

        }else {
            auto create_image_Volume = VolumecreateImageFormat(format);
            if (!create_image_Volume) {
                std::cerr << "Failed to create image format object." << std::endl;
                return false;
            };
            for (const auto& file : files) {
                auto processedImage_Volume = VolumeLoadImage(file, std::move(create_image_Volume));
                if (processedImage_Volume) {
                    //std::cout << "MetaData: " <<processedImage_Volume->getMetadata<< std::endl
                    //std::cout << "PixelData: " <<processedImage_Volume->getPixelValues<< std::endl
                    return true;
                }else {
                    std::cerr << "Processing image failed or image format not supported." << std::endl;
                };
                // Handle processedImage as needed
            };
        };
    } else {
        std::cerr << "Unsupported ENTRY" << std::endl;
        return false;
    };
    return 0;
};



