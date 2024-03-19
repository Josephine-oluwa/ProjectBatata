//NiftiFormat.h
#ifndef NIFTIFORMAT_H
#define NIFTIFORMAT_H

#pragma once

#include <iostream>
#include <sstream>
//#include <vector>
#include <string>
#include "nifti1_io.h"
#include "ImageLoader.h"

class NiftiFormat : public ImageLoader {
private:
    nifti_image* nifiFile = nullptr; // initialization of the nifti variable to loaded image data
    void clearImage(); // Utility function to clear the current image

public:
    bool load(const std::string& filename) override;
    bool save(const std::string& filename) override;
    std::string getMetadata() const override;
    std::vector<int> getPixelValues() const override;
    // NIFTI-specific methods...
};
#endif //NiftiFormat.h
