#pragma once

#pragma once


#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "../../tiny_obj_loader.h"

#include <iostream>
#include <vector>
/*Holds model data for Model3D*/
class ObjData {

	private:
		bool initialized;

	private:
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> material;
		tinyobj::attrib_t attributes;

		std::vector<GLuint> mesh_indices;

	public:
		ObjData();

		void LoadModel(std::string filename);
		bool isInitialized();

	public:
		std::vector<tinyobj::shape_t> getShapes();
		std::vector<tinyobj::material_t> getMaterial();
		tinyobj::attrib_t getAttributes();
		std::vector<GLuint> getMeshIndices();


};