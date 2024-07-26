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
#include "Project/ParticleContact.hpp"

#include "Project/Springs/AnchoredSpring.hpp"
#include "Project/Springs/ParticleSpring.hpp"

#include "Project/Utilities/RenderLine.hpp"
#include "config.hpp"

#include "Project/Link/Rod.hpp"
#include "Project/Link/ChainLink.hpp"
#include "Project/Link/BungeeLink.hpp"

using namespace managers;
using namespace std::chrono_literals;



int main(void)
{   

    GLFWwindow* window;
    srand(time(0));

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Quiz John Enrico Tolentino", NULL, NULL);
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



    World world = World();

    Model* m = new Model("3D/sphere.obj");
    m->assignShader(shader);
    m->transform.scale = Vector3::one * 30.f;

    Particle *p = new Particle();
    p->lifeSpan = 100;
  

    m->setColor(Vector3(0.6f,0,0));

    p->radius = 20;
    RenderParticle* p1 = new RenderParticle("p1", m, p);
    p1->particle->mass = 5;

    world.AddParticle(p1);

  
    Model* m2 = new Model(*m);
    m2->setColor(Vector3(0, 0, 0.6f));

    Particle* pp = new Particle(*p);
    pp->position = (Vector3::up + Vector3::right) * 100;
    pp->radius = 50;
    
    RenderParticle* p2 = new RenderParticle("p2", m2, pp);
    p2->particle->mass = 50;

    world.AddParticle(p2);

    /*

    ParticleSpring pSpring = ParticleSpring(pp, 5.f, 1.f);

    world.forceRegistry.Add(p, &pSpring);

    ParticleSpring pSpring2 = ParticleSpring(p, 5.f, 1.f);

    world.forceRegistry.Add(pp, &pSpring2);

    */

  

    //might try to make a time singleton to handle this

    constexpr std::chrono::nanoseconds timestep(16ms);
    using clock = std::chrono::high_resolution_clock;

    auto curr_time = clock::now();
    auto prev_time = curr_time;

    std::chrono::nanoseconds curr_ns(0);

    Vector3 anchorpoint1 = Vector3::left * 150 + Vector3::up * 200;
    Vector3 anchorpoint2 = Vector3::right * 150 + Vector3::up * 200;

    BungeeLink bungee = BungeeLink(anchorpoint1, 100, 20);
    ChainLink chain = ChainLink(anchorpoint2, p2->particle, 200);

    p->position = anchorpoint1 + Vector3::down * 100;
    pp->position = anchorpoint2;

    world.forceRegistry.Add(p1->particle, &bungee);
    world.forceRegistry.Add(p2->particle, &chain);

    RenderLine line = RenderLine(p2->particle->position, anchorpoint2, Vector3::one);
   
    RenderLine line2 = RenderLine(p1->particle->position, anchorpoint1, Vector3::one);

    #pragma region inputs

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

    #pragma endregion

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
                //contact.resolve(dT);
            }
                
            
        } 
       
        line.Update(p2->particle->position, anchorpoint2, CameraManager::getMain()->worldProjection);
        line2.Update(p1->particle->position, anchorpoint1, CameraManager::getMain()->worldProjection);
       


        world.Draw();

        CameraManager::DoOnAllCameras([x, y](Camera* camera) { camera->setRotation(Vector3(x, y, 0)); });
        CameraManager::getMain()->Draw();

        line.Draw();
        line2.Draw();


        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwTerminate();


    return 0;
}
