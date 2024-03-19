#include "MhdFormat.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool MhdFormat::load(const std::string& filename) {
    // Clear previous data
    pixelValues.clear();
    metadata.clear(); // Also clear previous metadata

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }
    // Temporary variables for parsing
    std::string line, key, value;
    std::string dataFileName; 
    // Parse the MHD file line by line
    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::getline(lineStream, key, '=');
        std::getline(lineStream, value);
        if (key == "ElementDataFile") {
            dataFileName = value;
        } else {
            // For simplicity, storing all metadata as a single string
            metadata += key + "=" + value + "\n";
        }
    }
    file.close();
    std::ifstream dataFile(dataFileName, std::ios::binary);
    if (!dataFile.is_open()) {
        std::cerr << "Failed to open data file: " << dataFileName << std::endl;
        return false;
    }
    int value;
    while (dataFile.read(reinterpret_cast<char*>(&value), sizeof(int))) {
        pixelValues.push_back(value);
    }
    dataFile.close();
    return true;
}

bool MhdFormat::save(const std::string& filename) {
    // Implementing save functionality might involve creating an MHD file and a separate data file.
    // This example won't cover save functionality due to its complexity and dependence on specific needs.
    std::cerr << "Save functionality is not implemented." << std::endl;
    return false;
}

std::string MhdFormat::getMetadata() const {
    return metadata;
}

std::vector<int> MhdFormat::getPixelValues() const {
    return pixelValues;
}
