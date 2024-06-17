#include "Camera.hpp"


Camera::Camera(Vector3 cameraPos, Vector3 cameraFront): cameraPos(cameraPos), cameraFront(cameraFront), shader(0) {}

void Camera::assignShader(Shader* shader){
	this->shader = shader;
}

Vector3 Camera::getPosition() {
	return this->cameraPos;
}

void Camera::setPosition(Vector3 pos) {
	this->cameraPos = pos;
}
