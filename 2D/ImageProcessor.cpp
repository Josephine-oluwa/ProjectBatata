#include <vector>
#include <memory>
#include <string>
#include "DicomFormat.h"
#include "NifiFormat.h"
#include "STLLoader.h"
#include "ImageProcessor.h"
#include "MhdFormat.h"

// Processor function to create specific image format objects
std::unique_ptr<ImageLoader> createImageFormat(const std::string& format) {
    if (format == "DICOM") {
        return std::make_unique<DicomFormat>();
    } else if (format == "NIFTI") {
        return std::make_unique<NiftiFormat>();
    }
    else if (format == "PNG") {
        return std::make_unique<PNGFormat>();
    }
    else if (format == "JPEG") {
        return std::make_unique<JPEGFormat>();
    }
    else if(format == "STL"){
        return std::make_unique<STLLoader>();
    }
    else if(format == "MHD"){
        return std::make_unique<MhdFormat>();
    }

    // Add other formats here...

    return nullptr; // Return nullptr if format is not recognized
}

// Function to load an image, perform operations, and save it
// Takes a filename and a smart pointer to the created image
std::unique_ptr<ImageLoader> LoadImage(const std::vector<std::string>& filename, std::unique_ptr<ImageLoader> createdImage) {
    if (!createdImage) {
        return nullptr; // Return nullptr if createdImage is null
    }
    createdImage->load(filename);
    //// Perform operations on the image
    //createdImage->save("processed_" + filename);
    return createdImage; // Return the processed image
}
