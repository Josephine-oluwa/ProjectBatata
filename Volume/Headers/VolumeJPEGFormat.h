#ifndef VOLUMEJPEGFORMAT_H
#define VOLUMEJPEGFORMAT_H

#include "ImageLoader.h"
#include <vector>
#include <jpeglib.h>

class VolumeJPEGFormat : public VolumeImageLoader {
private:
    std::vector<int> pixelValues;
    int width, height;

public:
    bool load(const std::string& filename) override;
    bool save(const std::string& filename) override { return false; } // Not implemented
    std::string getMetadata() const override;
    std::vector<int> getPixelValues() const override { return pixelValues; }
};

#endif // JPEGFORMAT_H
