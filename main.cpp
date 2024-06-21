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

int main(void)
{   
    int sizeInput = Input::returnIntInput();

    GLFWwindow* window;
    srand(time(0));

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Group5_Tolentino&Ong_Engine1_Phase1", NULL, NULL);
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

    // RenderParticleController is the class that handles the spawning of the particles //
    RenderParticleController renderparticleController = RenderParticleController(sizeInput);

    World world = World();

    //might try to make a time singleton to handle this

    constexpr std::chrono::nanoseconds timestep(16ms);
    using clock = std::chrono::high_resolution_clock;

    auto curr_time = clock::now();
    auto prev_time = curr_time;

    std::chrono::nanoseconds curr_ns(0);

    bool isPaused = false;

    Input& input = *Input::getInstance();

    input[GLFW_KEY_SPACE] += { GLFW_PRESS, [&isPaused]() {isPaused = !isPaused;} };
    input[GLFW_KEY_1] += { GLFW_PRESS, []() { CameraManager::switchToOrtho(); }};
    input[GLFW_KEY_2] += { GLFW_PRESS, []() { CameraManager::switchToPerspective(); }};


    float x = 0;
    float y = 0;
    float step = 0.1f;

    input[GLFW_KEY_W] += { GLFW_REPEAT, [&x, step]() { x += step; }};
    input[GLFW_KEY_S] += { GLFW_REPEAT, [&x, step]() { x -= step; }};

    input[GLFW_KEY_D] += { GLFW_REPEAT, [&y, step]() { y += step; }};
    input[GLFW_KEY_A] += { GLFW_REPEAT, [&y, step]() { y -= step; }};
    input[GLFW_KEY_BACKSPACE] += {GLFW_PRESS, [&x, &y] {x = 0; y=0;}};
 
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

        if (!isPaused && renderparticleController.triggerSpawn)
            world.AddParticle(renderparticleController.createRenderParticle());

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
