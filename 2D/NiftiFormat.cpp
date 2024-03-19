#include <iostream>
#include <sstream>
#include "Headers/NiftiFormat.h"

bool NiftiFormat::load(const std::string& filename) {
    clearImage(); 
    nifiFile = nifti_image_read(filename.c_str(),1)
    if (nii_img == nullptr) {
        std::cerr << "Failed to read NIfTI image." << std::endl;
        return false;
    }
    std::cout << "Loaded Successfuly " << std::endl;
    return true
}

bool NiftiFormat::save(const std::string& filename) {
    // Implementation for saving NIFTI
    if (!nifiFile) {
        std::cerr << "No image loaded to save." << std::endl;
        return false;
    }
    //nifti_set_filenames(nifiFile, filename.c_str(), 0, 0);
    //nifti_image_write(nifiFile);

    return true;
    
};

std::string NiftiFormat::getMetadata() const {
    if (!nifiFile) {
        std::cerr << "No image loaded" << std::endl;
        return false;
    }
    //return nifiFile->dim
};

std::vector<int> NiftiFormat::getPixelValues() const{
    if (!nifiFile) {
        std::cerr << "No image loaded" << std::endl;
        return false;
    }
    if (nifiFile->dim[0] !=2 ) {
        std::cerr << "Error: The NIfTI image is not 2D." << std::endl;
        nifti_image_free(nifiFile);
        return false; 
    }
    if (nifiFile->datatype != DT_FLOAT32) {
        std::cerr << "Error: The NIfTI image data type is not FLOAT32." << std::endl;
        nifti_image_free(nifiFile);
        return false; // Return an empty vector
    }
    
    float* data = static_cast<float*>(nifiFile->data);
    int nx = nifiFile->dim[1];
    int ny = nifiFile->dim[2];
    for (int y = 0; y < ny; ++y) {
        for (int x = 0; x < nx; ++x) {
            int index = x + y * nx;
            std::cout << "Voxel of(" << x << ", " << y << "): " << data[index] << std::endl;
        }
    }
    //nifti_image_free(nifiFile);
    return true
};


void NiftiFormat::clearImage() {
    if (nifiFile) {
        nifti_image_free(nifiFile);
        nifiFile = nullptr;
    }
}