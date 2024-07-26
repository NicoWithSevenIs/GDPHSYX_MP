#pragma once

#include "../Vector3.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

class RenderLine
{
	public:
		Vector3 p1;
		Vector3 p2;

		glm::mat4 projection_matrix;

		Vector3 color;

		RenderLine(Vector3 p1, Vector3 p2, Vector3 color): p1(p1), p2(p2), color(color){}

		void Update(Vector3 p1, Vector3 p2, glm::mat4 projection_matrix);
		void Draw();
};

