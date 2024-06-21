#include "PerspectiveCamera.hpp"
#include "../../config.hpp"


PerspectiveCamera::PerspectiveCamera(Vector3 cameraPos, Vector3 cameraFront): Camera(cameraPos, cameraFront) {}

void PerspectiveCamera::configureMatrices(glm::mat4& projection, glm::mat4& view)
{
    glm::vec3 pos = (glm::vec3)cameraPos;
    glm::vec3 front = (glm::vec3)(cameraPos + cameraFront);

    view = glm::lookAt(pos, front, (glm::vec3)Vector3::up);

    //view = glm::translate(view, -pos);
    view *= glm::toMat4(glm::quat((glm::vec3)this->rotation));
   // view = glm::translate(view, pos);

    //glm::mat4 projectionMatrix = glm::perspective(glm::radians(60.f), SCREEN_WIDTH / SCREEN_HEIGHT, 1.f, 1000.f);

    //https://community.khronos.org/t/pixel-perfect-projection-matrix/61435/2

    float near = 1;
    float far = 10000;
    float focal = 500;
    float aspectRatio = SCREEN_WIDTH / SCREEN_HEIGHT;


    float ymax = SCREEN_WIDTH / 2.0f * near / focal;
    float ymin = -ymax;
    float xmin = ymin * aspectRatio;
    float xmax = ymax * aspectRatio;

    projection = glm::frustum(xmin, xmax, ymin, ymax, near, far);
}


