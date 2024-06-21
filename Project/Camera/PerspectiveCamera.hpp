#pragma once

#include "Camera.hpp"

class PerspectiveCamera : public Camera {


	public:
		PerspectiveCamera(Vector3 cameraPos = Vector3(0, 0, 3), Vector3 cameraFront = Vector3(0, 0, -1));
		void Draw() override;




};