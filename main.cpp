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

void setCableCreatorParticles(Model* m, World* world, CableCreator* creator) {
    m->transform.scale.x = creator->particleRadius;
    m->transform.scale.y = creator->particleRadius;
    m->transform.scale.z = creator->particleRadius;

    RenderParticle* p1 = new RenderParticle("p1", m, creator->particles[0]);
    world->AddParticle(p1);

    RenderParticle* p2 = new RenderParticle("p2", m, creator->particles[1]);
    world->AddParticle(p2);

    RenderParticle* p3 = new RenderParticle("p3", m, creator->particles[2]);
    world->AddParticle(p3);

    RenderParticle* p4 = new RenderParticle("p4", m, creator->particles[3]);
    world->AddParticle(p4);

    RenderParticle* p5 = new RenderParticle("p5", m, creator->particles[4]);
    world->AddParticle(p5);
     
    world->forceRegistry.Add(creator->particles[0], creator->anchoredSprings[0]);
    world->forceRegistry.Add(creator->particles[1], creator->anchoredSprings[1]);
    world->forceRegistry.Add(creator->particles[2], creator->anchoredSprings[2]);
    world->forceRegistry.Add(creator->particles[3], creator->anchoredSprings[3]);
    world->forceRegistry.Add(creator->particles[4], creator->anchoredSprings[4]);

    //std::cout << "ball scale check: " << m->transform.scale.x << " ," << m->transform.scale.y << " ," << m->transform.scale.z << std::endl;
    std::cout << "anchoredSpring 0 x: " << creator->anchoredSprings[0]->anchorPoint.x << std::endl;
    std::cout << "anchoredSpring 1 x: " << creator->anchoredSprings[1]->anchorPoint.x << std::endl;
    std::cout << "anchoredSpring 2 x: " << creator->anchoredSprings[2]->anchorPoint.x << std::endl;
    std::cout << "anchoredSpring 3 x: " << creator->anchoredSprings[3]->anchorPoint.x << std::endl;
    std::cout << "anchoredSpring 4 x: " << creator->anchoredSprings[4]->anchorPoint.x << std::endl;

    std::cout << "anchoredSpring 0 y: " << creator->anchoredSprings[0]->anchorPoint.y << std::endl;
    std::cout << "anchoredSpring 1 y: " << creator->anchoredSprings[1]->anchorPoint.y << std::endl;
    std::cout << "anchoredSpring 2 y: " << creator->anchoredSprings[2]->anchorPoint.y << std::endl;
    std::cout << "anchoredSpring 3 y: " << creator->anchoredSprings[3]->anchorPoint.y << std::endl;
    std::cout << "anchoredSpring 4 y: " << creator->anchoredSprings[4]->anchorPoint.y << std::endl;
}

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
    m->setColor(Vector3(0.6f, 0, 0));

    Particle *p = new Particle();
    p->lifeSpan = 100;
    p->mass = 500;
    p->radius = 20;

    RenderParticle* p1 = new RenderParticle("p1", m, p);
    p1->particle->mass = 50;

    //m->setColor(Vector3(0.0f, 1, 0));




    Model* m2 = new Model("3D/sphere.obj");
    m2->assignShader(shader);
    m2->transform.scale = Vector3::one * 30.f;
    m2->setColor(Vector3(0, 0.6f, 0));

    Particle* pp = new Particle();
    pp->lifeSpan = 100;
    pp->position = Vector3(0, 20.f, 0);

    pp->radius = 20;

    RenderParticle* p2 = new RenderParticle("p2", m2, pp);
    p2->particle->mass = 50;
    

    //world.AddParticle(p2);

    Vector3 anchorPosition = Vector3::up * 50;
    Cable* c = new Cable(anchorPosition, p, 200);


    world.linkList.push_back(c);

    //auto aSpring = Cable(Vector3::up * 50, p, 200);
    //world.forceRegistry.Add(p, &aSpring);
  
    RenderLine line = RenderLine(anchorPosition, p->position, Vector3::one);

    //pp->radius = 20;
    //RenderParticle* rp = new RenderParticle("p1", m, pp);
    //rp->particle->mass = 5;

    //world.AddParticle(rp);

    CableCreator* creator = new CableCreator();
    
    //might try to make a time singleton to handle this

    //p->AddForce(Vector3(200000,200000,0));

    constexpr std::chrono::nanoseconds timestep(16ms);
    using clock = std::chrono::high_resolution_clock;

    auto curr_time = clock::now();
    auto prev_time = curr_time;

    std::chrono::nanoseconds curr_ns(0);

    #pragma region inputs

    bool isPaused = false;
    Input& input = *Input::getInstance();
    input.askCableInput(creator);
    creator->testPrint();

    creator->createCable();
    setCableCreatorParticles(m, &world, creator);


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

    input[GLFW_KEY_ENTER]+= { GLFW_PRESS, [p]() { p->AddForce(Vector3(1000000,100000, 0)); } };

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

        //std::cout << p->position << std::endl;
      
        line.Update(anchorPosition, p->position, CameraManager::getMain()->worldProjection);
       
        line.Draw();
        world.Draw();

        CameraManager::DoOnAllCameras([x, y](Camera* camera) { camera->setRotation(Vector3(x, y, 0)); });
        CameraManager::getMain()->Draw();


        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwTerminate();


    return 0;
}
