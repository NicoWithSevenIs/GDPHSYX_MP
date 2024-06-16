#include "OrthographicCamera.hpp"

OrthographicCamera::OrthographicCamera(Vector3 cameraPos, Vector3 cameraFront) : Camera(cameraPos, cameraFront)
{
    this->left = -5;
    this->bottom = -5;
    this->top = 5;
    this->right = 5;
    this->znear = -3;
    this->zfar = 1000;
}


void OrthographicCamera::Draw() {

    if (!this->shader) {
        std::cout << "[Error] No Shader assigned for Orthographic Camera" << std::endl;
        return;
    }


    glm::mat4 viewMatrix = glm::lookAt(
        (glm::vec3)this->cameraPos,
        (glm::vec3)this->cameraPos + (glm::vec3)this->cameraFront,
        (glm::vec3)Vector3::up
    );

    glm::mat4 projectionMatrix = glm::ortho(left, right, bottom, top, znear, zfar);

    unsigned int projectionLoc = glGetUniformLocation(this->shader->getShaderProg(), "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    unsigned int viewLoc = glGetUniformLocation(this->shader->getShaderProg(), "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

}

void OrthographicCamera::setOrthoData(float left, float right, float  bottom, float top, float znear, float zfar) {
    this->left = left;
    this->right = right;
    this->bottom = bottom;
    this->top = top;
    this->znear = znear;
    this->zfar = zfar;
}