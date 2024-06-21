#pragma once

#include "Camera.hpp"

class PerspectiveCamera : public Camera {

	protected:
		virtual void configureMatrices(glm::mat4& projection, glm::mat4& view);

	public:
		PerspectiveCamera(Vector3 cameraPos = Vector3(0, 0, 3), Vector3 cameraFront = Vector3(0, 0, -1));

};