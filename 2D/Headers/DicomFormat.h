//DicomFormat.h
#ifndef DICOMFORMAT_H
#define DICOMFORMAT_H

#pragma once

#include <iostream>
#include <sstream>
//#include <vector>
#include <string>
#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>
#include "ImageLoader.h"


class DicomFormat : public ImageLoader {
private:
    DcmFileFormat fileFormat;

public:
    bool load(const std::string& filename) override;
    bool save(const std::string& filename) override;
    std::string getMetadata() const override;
    std::vector<int> getPixelValues() const override;
    // DICOM-specific methods...
};

#endif //DicomFormat.h

