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
	//std::cout << "Created a Render Particle!" << std::endl;

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


	return renderParticle;
}

void RenderParticleController::intializeVelocities(RenderParticle* pRenderParticle) {

	Vector3 ub(140.f, 240.f, 300.f);
	Vector3 lb(-140.f, 50.f, -300.f);

	float vX = lb.x + r() * (ub.x - lb.x);
	float vY = lb.y + r() * (ub.y - lb.y);
	float vZ = lb.x + r() * (ub.z - lb.z);

	pRenderParticle->particle->setVelocity(Vector3(vX, vY, vZ));
	this->initializeDirection(pRenderParticle);
}	

void RenderParticleController::initializeAcceleration(RenderParticle* pRenderParticle) {

	Vector3 ub(15.f, 20.f, 59.f);
	Vector3 lb(10.f, 15.f, 45.f);

	float vX = lb.x + r() * (ub.x - lb.x);
	float vY = lb.y + r() * (ub.y - lb.y);
	float vZ = lb.z + r() * (ub.z - lb.z);

	//std::cout << "vX: " << vX << " vY: " << vY << " vZ: " << vZ << std::endl;
	pRenderParticle->particle->setAcceleration(Vector3(vX, vY, vZ));
	
}

void RenderParticleController::initializeDirection(RenderParticle* pRenderParticle) {

	Vector3 direction = this->getRandomVector();
	direction.Normalize();

	Vector3 vector = Vector3::Component(pRenderParticle->particle->getVelocity(), direction);
	vector.y = abs(vector.y);

	pRenderParticle->particle->setVelocity(vector);

}

void RenderParticleController::tickDown(World* refWorld, float deltaTime) {
	if (this->spawnTicks >= this->spawnInterval) {
		if (this->count <= this->size) { // count to check if the number of render particles set by user has already been spawned //
			this->triggerSpawn = true; // flag is set to true to allow spawning, this is to prevent render particles in being generated //
			//std::cout << "count: " << count << std::endl;
			this->spawnTicks = 0.0f;
			this->count+= 1;
		}
	}
	this->spawnTicks += deltaTime;
}

