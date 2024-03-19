#include <iostream>
#include <sstream>
#include "VolumeNiftiFormat.h"

bool VolumeNiftiFormat::load(const std::string& filename) {
    clearImage(); 
    nifiFile = nifti_image_read(filename.c_str(),1)
    if (nii_img == nullptr) {
        std::cerr << "Failed to read NIfTI image." << std::endl;
        return false;
    }
    std::cout << "Loaded Successfuly " << std::endl;
    return true
}

bool VolumeNiftiFormat::save(const std::string& filename) {
    // Implementation for saving NIFTI
    if (!nifiFile) {
        std::cerr << "No image loaded to save." << std::endl;
        return false;
    }
    //nifti_set_filenames(nifiFile, filename.c_str(), 0, 0);
    //nifti_image_write(nifiFile);

    return true;
    
}

std::string VolumeNiftiFormat::getMetadata() const {
    if (!nifiFile) {
        std::cerr << "No image loaded" << std::endl;
        return false;
    }
}

std::vector<int> VolumeNiftiFormat::getPixelValues() const{
    if (!nifiFile) {
        std::cerr << "No image loaded" << std::endl;
        return false;
    }
    if (nifiFile->dim[0] !>=3 ) {
        std::cerr << "Error: The NIfTI image is not 3D." << std::endl;
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
    int nz = nifiFile->dim[3];
    for (int z = 0; z < nz; ++z) {
            for (int y = 0; y < ny; ++y) {
                for (int x = 0; x < nx; ++x) {
                    int index = x + y*nx + z*nx*ny;
                    std::cout << "Voxel of(" << x << ", " << y << ", " << z << "): " << data[index] << std::endl;
                }
            }
    }
    //nifti_image_free(nifiFile);
    return true
};

void VolumeNiftiFormat::clearImage() {
    if (nifiFile) {
        nifti_image_free(nifiFile);
        nifiFile = nullptr;
    }
}