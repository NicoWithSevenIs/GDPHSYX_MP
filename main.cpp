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

#include "Project/Link/Cable.hpp"
#include "Project/Cable/CableCreator.hpp"

using namespace managers;
using namespace std::chrono_literals;




int main(void)
{   

          
    Input& input = *Input::getInstance();
    Vector3 pushForce;

    auto cableLength = 200;
    auto particleGap = 100;
    auto particleRadius = 50;
    auto gravityStrength = 9.81f;


    /*
     auto cableLength = input.getLine<float>("Cable Length");
    auto particleGap = input.getLine<float>("Particle Gap");
    auto particleRadius = input.getLine<float>("Particle Radius");
    auto gravityStrength = input.getLine<float>("Gravity Strength");

    
  
    std::cout << "Apply Force" << std::endl;
    pushForce.x = input.getLine<float>("x");
    pushForce.y = input.getLine<float>("y");
    pushForce.z = input.getLine<float>("z");
      */

    CableCreator* creator = new CableCreator(cableLength, particleGap, particleRadius, pushForce);

    CableSet cableset = creator->createCables();
    //setCableCreatorParticles(m, &world, creator);


    GLFWwindow* window;
    srand(time(0));

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Phase 2 - Lance Ong, Nico Tolentino", NULL, NULL);
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
    world.gravity.Gravity = Vector3::down * gravityStrength;

    std::vector<Model*> models;
    for (int i = 0; i < cableset.particles.size(); i++) {
        Model* m = new Model("3D/sphere.obj");
        m->assignShader(shader);
        m->setColor(Vector3(0.6f, 0, 0));

        models.push_back(m);
    }

    RenderParticle* rp = new RenderParticle("rp", models[0], new Particle());
    world.AddParticle(rp);
   /*

    for (int i = 0; i < cableset.particles.size(); i++) {
        RenderParticle* rp = new RenderParticle("rp" + std::to_string(i), models[i], cableset.particles);
        world.AddParticle(rp);
    }

    for (int i = 0; i < cableset.cables.size(); i++) {
        //world.linkList.push_back(cableset.cables[i]);
    }
    */

    std::vector<RenderLine> lines;

    for (auto c : cableset.cables) {
        RenderLine line = RenderLine(c->particles[0]->position, c->particles[1]->position, Vector3::one);
        lines.push_back(line);
    }
  



    

    constexpr std::chrono::nanoseconds timestep(16ms);
    using clock = std::chrono::high_resolution_clock;

    auto curr_time = clock::now();
    auto prev_time = curr_time;

    std::chrono::nanoseconds curr_ns(0);

    #pragma region inputs

    bool isPaused = false;
    input[GLFW_KEY_ENTER] += { GLFW_PRESS, [&isPaused]() {isPaused = !isPaused;} };
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


    bool hasStarted = false;
    input[GLFW_KEY_SPACE]+= { GLFW_PRESS, [&hasStarted, &creator]() 
        { 
            if (hasStarted) return;

            creator->leftMost->AddForce(Vector3(1000000, 100000, 0));
            hasStarted = true; 
        }
    };

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

            if (!isPaused)
                world.Update(dT);  
            
        } 

        /*
        for (int i = 0; i < lines.size(); i++) {

            Vector3 p1 = cableset.particles[0]->position;
            Vector3 p2 = cableset.particles[1]->position;

            lines[i].Update(p1 ,p2, CameraManager::getMain()->worldProjection);
            lines[i].Draw();
        }
  */
       

        world.Draw();

        CameraManager::DoOnAllCameras([x, y](Camera* camera) { camera->setRotation(Vector3(x, y, 0)); });
        CameraManager::getMain()->Draw();


        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwTerminate();


    return 0;
}
