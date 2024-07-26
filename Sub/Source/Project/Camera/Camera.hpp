#pragma once

#include "../../Project/Vector3.hpp"
#include "../Components/Shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GLFW/glfw3.h"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

class Camera {

	protected: 
		Vector3 cameraPos;
		Vector3 cameraFront;

		Shader* shader;

		Vector3 rotation;
	
	public:
		glm::mat4 worldProjection;

	public:
		Camera(Vector3 cameraPos = Vector3(0,0,3), Vector3 cameraFront = Vector3(0, 0, -1));


	protected:

		//configuration for view and projection matrices, it's called in draw just before said matrices are fed to the shader
		virtual void configureMatrices(glm::mat4& projection, glm::mat4& view);

	public:
		void Draw();
		
		void assignShader(Shader* shader);
		
		Vector3 getPosition();
		void setPosition(Vector3 pos);
		
		Vector3 getFront();
		void setFront(Vector3 front);

		Vector3 getRotation();
		void setRotation(Vector3 rotation);

};