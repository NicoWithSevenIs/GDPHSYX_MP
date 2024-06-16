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

    ShaderManager::getInstance()->buildShaders();

    //glViewport(0, 0, window_width, window_height);

    Shader* shader = (*ShaderManager::getInstance())[ShaderNames::MODEL_SHADER];
    CameraManager::getCamera()->assignShader(shader);
    OrthographicCamera* ortho = (OrthographicCamera*) CameraManager::getCamera();
    ortho->setOrthoData(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);

    World world = World();


    /* GREEN (NE) */
    Model* m = new Model("3D/sphere.obj");
    m->transform.scale = Vector3(10, 10, 10);
    m->assignShader(shader);
    m->setColor(Vector3(0, 1, 0));

    Particle* p = new Particle();
    p->setPosition(Vector3(300,300,173));

    //oh lord i feel like wet spaghetti rn so i guess ill be doing this instead
    //Shaboomboom(p, 90, 8);
   
    p->mass = 3;
    p->AddForce(Vector3(-6000,0,0));


    /* RED (NW) */
    Model* m2 = new Model(*m);
    m2->setColor(Vector3(1, 0, 0));

    Particle* p2 = new Particle();
    p2->setPosition(Vector3(-300, 300, 201));
    Shaboomboom(p2, 80, 14.5f);

    /* BLUE (SE) */
    Model* m3 = new Model(*m);
    m3->setColor(Vector3(0, 0, 1));

    Particle* p3 = new Particle();
    p3->setPosition(Vector3(300, -300, -300));
    Shaboomboom(p3, 130, 1);


    /* YELLOW (SW) */
    Model* m4 = new Model(*m);
    m4->setColor(Vector3(1, 1, 0));

    Particle* p4 = new Particle();
    p4->setPosition(Vector3(-300, -300, -150));
    Shaboomboom(p4, 110, 3);

    world.AddParticle(new RenderParticle("Green", m, p));
    world.AddParticle(new RenderParticle("Red", m2, p2));
    world.AddParticle(new RenderParticle("Blue", m3, p3));
    world.AddParticle(new RenderParticle("Yellow", m4, p4));

    //might try to make a time singleton to handle this

    constexpr std::chrono::nanoseconds timestep(16ms);
    using clock = std::chrono::high_resolution_clock;

    auto curr_time = clock::now();
    auto prev_time = curr_time;

    std::chrono::nanoseconds curr_ns(0);


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
            world.Update(dT);
        }

        CameraManager::getCamera()->Draw();
        world.Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();

        if(world.allInCenter())
            break;
    }

    world.printResults();
    glfwTerminate();

    std::cout << "Press [ENTER] to continue..." << std::endl;
    getchar();

    return 0;
}
