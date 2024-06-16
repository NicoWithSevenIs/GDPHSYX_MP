#include "Camera.hpp"


Camera::Camera(Vector3 cameraPos, Vector3 cameraFront): cameraPos(cameraPos), cameraFront(cameraFront), shader(0) {}

void Camera::assignShader(Shader* shader){
	this->shader = shader;
}