//PNGFormat.h
#ifndef VOLUMEPNGFormat_H
#define VOLUMEPNGFormat_H

#pragma once

#include <iostream>
#include <sstream>
//#include <vector>
#include <string>
#include <png.h>
#include "ImageLoader.h"


class VolumePNGFormat : public VolumeImageLoader {
private:
    std::vector<int> pixelValues;
    int width, height;

public:
    bool load(const std::string& filename) override;
    bool save(const std::string& filename) override { return false; } // Not implemented
    std::string getMetadata() const override;
    std::vector<int> getPixelValues() const override { return pixelValues; }
};

#endif //PNGFormat.h

