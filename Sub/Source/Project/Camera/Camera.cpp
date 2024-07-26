#include "Camera.hpp"


Camera::Camera(Vector3 cameraPos, Vector3 cameraFront): cameraPos(cameraPos), cameraFront(cameraFront), shader(0) {}

void Camera::configureMatrices(glm::mat4& projection, glm::mat4& view){}

void Camera::Draw()
{

	glm::vec3 pos = (glm::vec3)cameraPos;
	glm::vec3 front = (glm::vec3)(cameraPos + cameraFront);

	if (!this->shader) {
		std::cout << "[Error] No Shader assigned to the Camera" << std::endl;
		return;
	}

	glm::mat4 projectionMatrix = glm::mat4(1.f);
	glm::mat4 viewMatrix = glm::lookAt(pos, front, (glm::vec3)Vector3::up);

	this->configureMatrices(projectionMatrix, viewMatrix);

	this->worldProjection = projectionMatrix * viewMatrix;

	unsigned int projectionLoc = glGetUniformLocation(this->shader->getShaderProg(), "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	unsigned int viewLoc = glGetUniformLocation(this->shader->getShaderProg(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

}

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
