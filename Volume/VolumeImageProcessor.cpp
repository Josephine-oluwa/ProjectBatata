#include <memory>
#include <string>
#include "Headers/VolumeDicomFormat.h"
#include "Headers/VolumeNiftiFormat.h"
#include "Headers/VolumeImageProcessor.h"

// Processor function to create specific image format objects
std::unique_ptr<VolumeImageLoader> VolumecreateImageFormat(const std::string& format) {
    if (format == "DICOM") {
        return std::make_unique<VolumeDicomFormat>();
    } else if (format == "NIFTI") {
        return std::make_unique<VolumeNiftiFormat>();
    }
    } else if (format == "PNG") {
        return std::make_unique<VolumePNGFormat>();
    }
    } else if (format == "JPEG") {
        return std::make_unique<VolumeJPEGFormat>();
    }

    // Add other formats here...

    return nullptr; // Return nullptr if format is not recognized
}

// Function to load an image, perform operations, and save it
// Takes a filename and a smart pointer to the created image
std::unique_ptr<VolumeImageLoader> VolumeLoadImage(const std::vector<std::string>& filename, std::unique_ptr<VolumeImageLoader> createdImage) {
    if (!createdImage) {
        return nullptr; // Return nullptr if createdImage is null
    }
    createdImage->load(filename);
    //// Perform operations on the image
    //createdImage->save("processed_" + filename);
    return createdImage; // Return the processed image
}
