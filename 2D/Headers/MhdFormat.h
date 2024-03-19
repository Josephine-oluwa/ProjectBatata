#ifndef MHDFORMAT_H
#define MHDFORMAT_H

#include "ImageLoader.h"
#include <vector>
#include <string>

class MhdFormat : public ImageLoader {
private:
    std::vector<int> pixelValues;
    std::string metadata;
public:
    MhdFormat() = default;
    virtual ~MhdFormat() override = default;

    virtual bool load(const std::string& filename) override;
    virtual bool save(const std::string& filename) override;
    virtual std::string getMetadata() const override;
    virtual std::vector<int> getPixelValues() const override;
};

#endif 
