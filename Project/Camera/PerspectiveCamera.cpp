#include "PerspectiveCamera.hpp"
#include "../../config.hpp"

PerspectiveCamera::PerspectiveCamera(Vector3 cameraPos, Vector3 cameraFront) {}

void PerspectiveCamera::Draw(){

    glm::vec3 pos = (glm::vec3)cameraPos;
    glm::vec3 front = (glm::vec3)(cameraFront+cameraFront);

    
    glm::mat4 viewMatrix = glm::lookAt(pos, front, (glm::vec3)Vector3::up);
 

    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.f), SCREEN_WIDTH / SCREEN_HEIGHT, -3.f, 1000.f);


    unsigned int projectionLoc = glGetUniformLocation(this->shader->getShaderProg(), "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    unsigned int viewLoc = glGetUniformLocation(this->shader->getShaderProg(), "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
}
