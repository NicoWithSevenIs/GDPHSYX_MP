#include "OrthographicCamera.hpp"

void OrthographicCamera::configureMatrices(glm::mat4& projection, glm::mat4& view)
{

    glm::vec3 pos = (glm::vec3)cameraPos;
    glm::vec3 front = (glm::vec3)(cameraPos + cameraFront);


    view = glm::lookAt(pos, front, (glm::vec3)Vector3::up);

    //view = glm::translate(view, -pos);
    view *= glm::toMat4(glm::quat((glm::vec3)this->rotation));
    //view = glm::translate(view, pos);


    projection = glm::ortho(left, right, bottom, top, znear, zfar);

}

OrthographicCamera::OrthographicCamera(Vector3 cameraPos, Vector3 cameraFront) : Camera(cameraPos, cameraFront)
{
    this->left = -5;
    this->bottom = -5;
    this->top = 5;
    this->right = 5;
    this->znear = -3;
    this->zfar = 1000;
}

void OrthographicCamera::setOrthoData(float left, float right, float  bottom, float top, float znear, float zfar) {
    this->left = left;
    this->right = right;
    this->bottom = bottom;
    this->top = top;
    this->znear = znear;
    this->zfar = zfar;
}