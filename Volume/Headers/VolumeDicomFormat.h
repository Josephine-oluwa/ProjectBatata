#ifndef VOLUMEDICOMFORMAT_H
#define VOLUMEDICOMFORMAT_H

#pragma once

#include <iostream>
#include <sstream>
//#include <vector>
#include <string>
#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>
#include "VolumeImageLoader.h"

class VolumeDicomFormat : public VolumeImageLoader {
private:
    DcmFileFormat fileFormat;

public:
    bool load(const std::string& filename) override;
    bool save(const std::string& filename) override;
    std::string getMetadata() const override;
    std::vector<int> getPixelValues() const override;
    // DICOM-specific methods...
};
#endif
