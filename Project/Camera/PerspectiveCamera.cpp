#include "PerspectiveCamera.hpp"
#include "../../config.hpp"

PerspectiveCamera::PerspectiveCamera(Vector3 cameraPos, Vector3 cameraFront): Camera(cameraPos, cameraFront) {}

void PerspectiveCamera::Draw(){

    glm::vec3 pos = (glm::vec3)cameraPos;
    glm::vec3 front = (glm::vec3)(cameraPos+cameraFront);

    
    glm::mat4 viewMatrix = glm::lookAt(pos, front, (glm::vec3)Vector3::up);
 
 
    //glm::mat4 projectionMatrix = glm::perspective(glm::radians(60.f), SCREEN_WIDTH / SCREEN_HEIGHT, 1.f, 1000.f);

   
   

    //https://community.khronos.org/t/pixel-perfect-projection-matrix/61435/2

    float near = 1;
    float far = 1000;
    float focal = 500;
    float aspectRatio = SCREEN_WIDTH/SCREEN_HEIGHT;


    float ymax = SCREEN_WIDTH / 2.0f * near / focal;
    float ymin = -ymax;
    float xmin = ymin * aspectRatio;
    float xmax = ymax * aspectRatio;
    glm::mat4 projectionMatrix = glm::frustum(xmin, xmax, ymin, ymax, near, far);
    /* */

    unsigned int projectionLoc = glGetUniformLocation(this->shader->getShaderProg(), "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    unsigned int viewLoc = glGetUniformLocation(this->shader->getShaderProg(), "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
}
