#include "RenderParticleController.hpp"

RenderParticleController::RenderParticleController(int size) {
	this->size = size; // size refers to the user-defined size or amount //
	this->count = 0;
	this->spawnInterval = 0.05f;
	this->spawnTicks = 0.0f;
	this->triggerSpawn = false; // a flag that is modified to true for when spawnTicks hit the spawnInterval and is turned off after spawning one render particle // 
}

// spawns a render particle that is added to the World class in main.cpp //
RenderParticle* RenderParticleController::createRenderParticle() {
	Shader* shader = (*ShaderManager::getInstance())[ShaderNames::MODEL_SHADER];
	Model* pModel = new Model("3D/sphere.obj");
	Particle* pParticle = new Particle();
	RenderParticle* renderParticle = new RenderParticle("Sphere", pModel, pParticle);

	// Randomization for lifespawn from 1 to 10 seconds //
	float lifeSpanRand = static_cast<float>(rand()) / RAND_MAX;
	lifeSpanRand = 1.0f + lifeSpanRand * (10.0f - 1.0f + 1.0f);
	renderParticle->particle->lifeSpan = lifeSpanRand;

	float r = static_cast<float>(rand()) / RAND_MAX;
	float g = static_cast<float>(rand()) / RAND_MAX;
	float b = static_cast<float>(rand()) / RAND_MAX;

	renderParticle->model->setColor(Vector3(r, g, b));

	renderParticle->particle->setPosition(Vector3(0, -300, 0));
	renderParticle->model->assignShader(shader);

	// Randomization for model radius //
	float radius = static_cast<float>(rand()) / RAND_MAX;
	radius = 2.0f + radius * (10.0f - 2.0f + 1.0f);

	renderParticle->model->transform.scale = Vector3(radius, radius, radius);

	// Randomization for the velocities and accelerations //
	// values for upperbounds and lowerbounds are pre-defined // 
	this->intializeVelocities(renderParticle);
	this->initializeAcceleration(renderParticle);

	this->triggerSpawn = false;

	return renderParticle;
}

void RenderParticleController::intializeVelocities(RenderParticle* pRenderParticle) {
	float vX_ub = 140.0f;
	float vY_ub = 240.0f;
	float vZ_ub = 300.0f;

	float vX_lb = -140.0f;
	float vY_lb = 50.0f;
	float vZ_lb = -300.0f;

	float vX_random = static_cast<float>(rand()) / RAND_MAX;
	float vY_random = static_cast<float>(rand()) / RAND_MAX;
	float vZ_random = static_cast<float>(rand()) / RAND_MAX;

	float vX = vX_lb + vX_random * (vX_ub - vX_lb);
	float vY = vY_lb + vY_random * (vY_ub - vY_lb);
	float vZ = vZ_lb + vZ_random * (vZ_ub - vZ_lb);

	//std::cout << "vX: " << vX << " vY: " << vY << " vZ: " << vZ << std::endl;
	pRenderParticle->particle->setVelocity(Vector3(vX, vY, vZ));
	this->initializeDirection(pRenderParticle);
	
}	

void RenderParticleController::initializeAcceleration(RenderParticle* pRenderParticle) {
	float vX_ub = 15.0f;
	float vY_ub = 20.0f;
	float vZ_ub = 59.0f;

	float vX_lb = 10.0f;
	float vY_lb = 15.0f;
	float vZ_lb = 45.0f;

	float vX_random = static_cast<float>(rand()) / RAND_MAX;
	float vY_random = static_cast<float>(rand()) / RAND_MAX;
	float vZ_random = static_cast<float>(rand()) / RAND_MAX;

	float vX = vX_lb + vX_random * (vX_ub - vX_lb);
	float vY = vY_lb + vY_random * (vY_ub - vY_lb);
	float vZ = vZ_lb + vZ_random * (vZ_ub - vZ_lb);

	//std::cout << "vX: " << vX << " vY: " << vY << " vZ: " << vZ << std::endl;
	pRenderParticle->particle->setAcceleration(Vector3(vX, vY, vZ));
	
}

void RenderParticleController::initializeDirection(RenderParticle* pRenderParticle) {
	float direction_x = static_cast<float>(rand()) / RAND_MAX;
	float direction_y = static_cast<float>(rand()) / RAND_MAX;
	float direction_z = static_cast<float>(rand()) / RAND_MAX;

	Vector3 direction = Vector3(direction_x, direction_y, direction_z);
	direction.Normalize();

	Vector3 vector = pRenderParticle->particle->getVelocity();
	float x = vector.x * direction.x;
	float y = vector.y * direction.y;
	float z = vector.z * direction.z;

	y = abs(y);
	pRenderParticle->particle->setVelocity(Vector3(x, y, z));
}

void RenderParticleController::tickDown(World* refWorld, float deltaTime) {
	if (this->spawnTicks >= this->spawnInterval) {
		if (this->count != this->size) { // count to check if the number of render particles set by user has already been spawned //
			this->triggerSpawn = true; // flag is set to true to allow spawning, this is to prevent render particles in being generated //
			this->spawnTicks = 0.0f;
			this->count++;
		}
	}
	this->spawnTicks += deltaTime;
}

