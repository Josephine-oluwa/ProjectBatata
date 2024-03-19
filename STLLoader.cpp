#include "STLLoader.h"

STLLoader::STLLoader() : stl_reader::StlMesh<float, unsigned int>() {}

bool STLLoader::loadStlFile(const std::string& filename) {
    return this->read_file(filename);
}

void STLLoader::getGeometry(std::vector<std::array<float, 3>>& vertices, std::vector<std::array<unsigned int, 3>>& triangles) const {
    vertices.clear();
    triangles.clear();

    for (size_t i = 0; i < this->num_vrts(); ++i) {
        std::array<float, 3> vertex = {this->vrts_[3 * i], this->vrts_[3 * i + 1], this->vrts_[3 * i + 2]};
        vertices.push_back(vertex);
    }

    for (size_t i = 0; i < this->num_tris(); ++i) {
        std::array<unsigned int, 3> triangle = {this->tris_[3 * i], this->tris_[3 * i + 1], this->tris_[3 * i + 2]};
        triangles.push_back(triangle);
    }
}

std::string STLLoader::getMetadata() const {
    std::stringstream metadata;
    metadata << "Number of vertices: " << this->num_vrts() << "\n";
    metadata << "Number of triangles: " << this->num_tris() << "\n";
    metadata << "Number of solids: " << this->num_solids() << "\n";
    return metadata.str();
}
