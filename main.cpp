#include "glad/glad.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>
#include <typeinfo>

#define TINYOBJLOADER_IMPLEMENTATION 
//#include "tiny_obj_loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <string>
#include <chrono>

#include "Project/Vector3.hpp"
#include "Project/Managers/ShaderManager.hpp"
#include "Project/Components/ShaderNames.hpp"
#include "Project/Managers/CameraManager.hpp"
#include "Project/Managers/Input.hpp"
#include "Project/Particle.hpp"
#include "Project/Model.h"



#include "Project/World.hpp"
#include "Project/Controllers/RenderParticleController/RenderParticleController.hpp"

#include "config.hpp"


using namespace managers;
using namespace std::chrono_literals;

//will fix encapsulation issues on another day haha

/*
    Fires the sphere towards the origin
*/
void Shaboomboom(Particle* p, float velocity, float acceleration) {
    Vector3 dir = p->getPosition();
    dir.Normalize();
    dir *= -1;

    p->setVelocity(dir * velocity);
    //p->setAcceleration(dir * acceleration);
}

int main(void)
{
    GLFWwindow* window;
    srand(time(0));

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PC01 John Enrico Tolentino", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();

    glfwSetKeyCallback(window, Input::keyCallback);
    glfwSetCursorPosCallback(window, Input::mouseCallback);

    ShaderManager::getInstance()->buildShaders();

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    Shader* shader = (*ShaderManager::getInstance())[ShaderNames::MODEL_SHADER];
    CameraManager::initializeCameras(shader);

    RenderParticleController renderparticleController = RenderParticleController(1000);

    World world = World();

    //might try to make a time singleton to handle this

    constexpr std::chrono::nanoseconds timestep(16ms);
    using clock = std::chrono::high_resolution_clock;

    auto curr_time = clock::now();
    auto prev_time = curr_time;

    std::chrono::nanoseconds curr_ns(0);

    bool isPaused = false;

    Input* i = Input::getInstance();

    (*i)[GLFW_KEY_SPACE] += { GLFW_PRESS, [&isPaused]() {isPaused = !isPaused;} };
    (*i)[GLFW_KEY_1] += { GLFW_PRESS, []() { CameraManager::switchToOrtho(); }};
    (*i)[GLFW_KEY_2] += { GLFW_PRESS, []() { CameraManager::switchToPerspective(); }};


    float x = 0;
    float y = 0;
    float step = 0.1f;

    (*i)[GLFW_KEY_W] += { GLFW_REPEAT, [&x, step]() { x += step; }};
    (*i)[GLFW_KEY_S] += { GLFW_REPEAT, [&x, step]() { x -= step; }};

    (*i)[GLFW_KEY_D] += { GLFW_REPEAT, [&y, step]() { y += step; }};
    (*i)[GLFW_KEY_A] += { GLFW_REPEAT, [&y, step]() { y -= step; }};
   

    float lastX, lastY;
    float pitch = 0.f;
    float yaw = -90.f;
    bool firstMouse = true;
    glm::vec3 cameraFront;

    (*i) += [&lastX, &lastY, &pitch, &yaw, &firstMouse, &cameraFront](float xpos, float ypos) {

        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;

        float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(direction);

        //std::cout << xpos << "," << ypos << std::endl;
   
    };


    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    while (!glfwWindowShouldClose(window))
    {
 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        curr_time = clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::nanoseconds> (curr_time - prev_time);
        prev_time = curr_time;
        curr_ns += dur;

        if (curr_ns >= timestep) {
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(curr_ns);
            curr_ns -= curr_ns;

            float dT = (float)ms.count() / 1000;

            if (!isPaused){
                world.Update(dT);
                
            }
                
            
        } 
        renderparticleController.tickDown(&world, 0.01f);
        CameraManager::DoOnAllCameras([x,y](Camera* camera) { camera->setRotation(Vector3(x, y, 0)); } );
        CameraManager::getMain()->Draw();
        world.Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwTerminate();


    return 0;
}
