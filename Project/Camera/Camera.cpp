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


Vector3 Camera::getFront() {
	return this->cameraFront;
}

void Camera::setFront(Vector3 front) {
	this->cameraFront = front;
}

Vector3 Camera::getRotation()
{
	return this->rotation;
}

void Camera::setRotation(Vector3 rotation)
{
	this->rotation = rotation;
}
