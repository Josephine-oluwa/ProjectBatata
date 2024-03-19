//IMAGELOADER.h
#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#pragma once
#include <vector>
#include <string>
#include <memory>

class ImageLoader {    
public:
    virtual ~ImageLoader() {}
    // Load image from file
    virtual bool load(const std::string& filename) = 0;

    // Save image to file
    virtual bool save(const std::string& filename) = 0;

    // Access metadata
    virtual std::string getMetadata() const = 0;
    // Get pixel values
    virtual std::vector<int> getPixelValues() const = 0;

};
#endif //IMAGELOADER.h

