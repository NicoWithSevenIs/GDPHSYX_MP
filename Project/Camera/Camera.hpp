#pragma once

#include "../../Project/Vector3.hpp"
#include "../Components/Shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {

	protected: 
		Vector3 cameraPos;
		Vector3 cameraFront;

		Shader* shader;

	public:
		Camera(Vector3 cameraPos = Vector3(0,0,3), Vector3 cameraFront = Vector3(0, 0, -1));

	public:
		virtual void Draw() = 0;
		void assignShader(Shader* shader);
		
		void getPosition();
		void setPosition();

};