#pragma once

#include "Camera.hpp"

class OrthographicCamera : public Camera {
	
	private:
		float top, bottom, left, right;
		float znear;
		float zfar;

	protected:
		virtual void configureMatrices(glm::mat4& projection, glm::mat4& view) override;

	public:
		OrthographicCamera(Vector3 cameraPos = Vector3(0, 0, 3), Vector3 cameraFront = Vector3(0, 0, -1));
		void setOrthoData(float left, float right, float  bottom, float top, float znear = -3.f, float zfar = 1000.f);

};