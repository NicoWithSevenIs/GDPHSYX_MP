#pragma once

#include "Camera.hpp"
#include "GLFW/glfw3.h"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
class PerspectiveCamera : public Camera {


	protected:
		Vector3 rotation;


	public:
		PerspectiveCamera(Vector3 cameraPos = Vector3(0, 0, 3), Vector3 cameraFront = Vector3(0, 0, -1));
		void Draw() override;


		Vector3 getRotation();
		void setRotation(Vector3 rotation);

};