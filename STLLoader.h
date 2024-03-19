#ifndef STLLOADER_H
#define STLLOADER_H

#include <vector>
#include <array>
#include <string>
#include <sstream> 
#include "stl_reader.h"

class STLLoader : public stl_reader::StlMesh<float, unsigned int> {
public:
    STLLoader();

    bool loadStlFile(const std::string& filename);
    void getGeometry(std::vector<std::array<float, 3>>& vertices, std::vector<std::array<unsigned int, 3>>& triangles) const;
    std::string getMetadata() const; // Declare the getMetadata method
};

#endif 
