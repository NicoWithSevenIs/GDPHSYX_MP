#include "ObjData.hpp"

ObjData::ObjData() : initialized(false) {}

void ObjData::LoadModel(std::string filename) {

    std::string warning, error;

    this->initialized = tinyobj::LoadObj(
        &this->attributes,
        &this->shapes,
        &this->material,
        &warning,
        &error,
        filename.c_str()
    );

    //if (!warning.empty())
        //std::cout << "[WARNING] " << warning << std::endl;

    if (!error.empty()) {
        std::cout << "[ERROR] " << error << std::endl;
        shapes.clear();
        material.clear();
        return;
    }


    for (int i = 0; i < shapes[0].mesh.indices.size(); i++) 
        this->mesh_indices.push_back(shapes[0].mesh.indices[i].vertex_index);
 
}

bool ObjData::isInitialized() {
    return this->initialized;
}

std::vector<tinyobj::shape_t>  ObjData::getShapes() {
    return this->shapes;
}

std::vector<tinyobj::material_t>  ObjData::getMaterial() {
    return this->material;
}

tinyobj::attrib_t  ObjData::getAttributes() {
    return this->attributes;
}

std::vector<GLuint> ObjData::getMeshIndices() {
    return this->mesh_indices;
}
