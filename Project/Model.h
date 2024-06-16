#pragma once


/*
	
	[IMPORTANT REFERENCE]

		- I can't stress enough how important this reference material is:
		https://open.spotify.com/album/64SX9Efb2JGW3rJFE1ZddJ?si=jzEpg9cLTny9mj5L31JQdQ

*/

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Components/ObjData.hpp"
#include "Components/Transform.hpp"
#include "Components/Shader.hpp"

class Model{

	public:
		Transform transform;

	private:
		ObjData objData;
		Shader* shader = nullptr;
		Vector3 color = Vector3::one;


	private:
		GLuint VBO, VAO, EBO;

	public:
		Model(std::string filename);
		//Model(const Model& other);
		~Model();

	public:
		void Draw();
		void assignShader(Shader* shader);
		void setColor(Vector3 color);

	private:
		void initializeBuffers();

};