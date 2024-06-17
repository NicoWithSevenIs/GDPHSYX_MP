#include "glad/glad.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

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

    if (!glfwInit())
        return -1;

    float window_width = 500.f;
    float window_height = 500.f;

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PC01 John Enrico Tolentino", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();

    glfwSetKeyCallback(window, Input::keyCallback);

    ShaderManager::getInstance()->buildShaders();

    //glViewport(0, 0, window_width, window_height);

    Shader* shader = (*ShaderManager::getInstance())[ShaderNames::MODEL_SHADER];
    CameraManager::initializeCameras(shader);

    World world = World();


    /* GREEN (NE) */
    Model* m = new Model("3D/sphere.obj");
    m->transform.scale = Vector3(10, 10, 10);
    m->assignShader(shader);
    m->setColor(Vector3(0, 1, 0));

    Particle* p = new Particle();
    p->setPosition(Vector3(0,0,0));

    p->mass = 3;
    p->AddForce(Vector3(-6000,0,0));


    world.AddParticle(new RenderParticle("Green", m, p));

    //might try to make a time singleton to handle this

    constexpr std::chrono::nanoseconds timestep(16ms);
    using clock = std::chrono::high_resolution_clock;

    auto curr_time = clock::now();
    auto prev_time = curr_time;

    std::chrono::nanoseconds curr_ns(0);

    bool isPaused = false;

    (*Input::getInstance())[GLFW_KEY_SPACE] += { GLFW_PRESS, [&isPaused]() {isPaused = !isPaused;} };

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

            if (!isPaused) {
           
                world.Update(dT);
            }
           
        }

   
        CameraManager::getMain()->Draw();
        world.Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwTerminate();


    return 0;
}
