#include "RenderParticleController.hpp"

RenderParticleController::RenderParticleController(int size) {
	this->size = size;
	this->spawnInterval = 5.0f;
	this->spawnTicks = 0.0f;
}

std::list<RenderParticle*> RenderParticleController::createRenderParticles() {
	std::list<RenderParticle*> spawnedParticles = std::list<RenderParticle*>();

	for (int i = 0; i < this->size; i++) {
		
		Shader* shader = (*ShaderManager::getInstance())[ShaderNames::MODEL_SHADER];
		Model* pModel = new Model("3D/sphere.obj");
		Particle* pParticle = new Particle();
		RenderParticle* renderParticle = new RenderParticle("Sphere", pModel, pParticle);

		float r = static_cast<float>(rand()) / RAND_MAX;
		float g = static_cast<float>(rand()) / RAND_MAX;
		float b = static_cast<float>(rand()) / RAND_MAX;
		
		renderParticle->model->setColor(Vector3(r, g, b));
		
		renderParticle->particle->setPosition(Vector3(0, -300, 0));
		renderParticle->model->assignShader(shader);

		renderParticle->model->transform.scale = Vector3(5, 5, 5);
		this->intializeVelocities(renderParticle);
		this->initializeAcceleration(renderParticle);
		spawnedParticles.push_back(renderParticle);
	}
	return spawnedParticles;
}

void RenderParticleController::intializeVelocities(RenderParticle* pRenderParticle) {
	float vX_ub = 140.0f;
	float vY_ub = 240.0f;
	float vZ_ub = 10.0f;

	float vX_lb = -140.0f;
	float vY_lb = 50.0f;
	float vZ_lb = -10.0f;

	float vX_random = static_cast<float>(rand()) / RAND_MAX;
	float vY_random = static_cast<float>(rand()) / RAND_MAX;
	float vZ_random = static_cast<float>(rand()) / RAND_MAX;

	float vX = vX_lb + vX_random * (vX_ub - vX_lb);
	float vY = vY_lb + vY_random * (vY_ub - vY_lb);
	float vZ = vZ_lb + vZ_random * (vZ_ub - vZ_lb);

	std::cout << "vX: " << vX << " vY: " << vY << " vZ: " << vZ << std::endl;
	
	Vector3 dir = pRenderParticle->particle->getPosition();
	dir.Normalize();
	//vX *= dir.x * -1;
	//vY *= dir.y * -1;
	//vZ *= dir.z * -1;
	
	pRenderParticle->particle->setVelocity(Vector3(vX, vY, vZ));
}	

void RenderParticleController::initializeAcceleration(RenderParticle* pRenderParticle) {
	float aX_ub = 15.0f;
	float aY_ub = 15.0f;
	float aZ_ub = 15.0f;

	float aX_lb = 5.0f;
	float aY_lb = 5.0f;
	float aZ_lb = 5.0f;

	float aX_random = static_cast<float>(rand()) / RAND_MAX;
	float aY_random = static_cast<float>(rand()) / RAND_MAX;
	float aZ_random = static_cast<float>(rand()) / RAND_MAX;

	float aX = aX_lb + aX_random * (aX_ub - aX_lb);
	float aY = aY_lb + aY_random * (aY_ub - aY_lb);
	float aZ = aZ_lb + aZ_random * (aZ_ub - aZ_lb);

	std::cout << "aX: " << aX << " aY: " << aY << " aZ: " << aZ << std::endl;

	Vector3 dir = pRenderParticle->particle->getPosition();
	dir.Normalize();
	/*aX *= dir.x * -1;
	aY *= dir.y * -1;
	aZ *= dir.z * -1;*/

	pRenderParticle->particle->setAcceleration(Vector3(aX, aY, aZ));
}

void RenderParticleController::OnActivate(std::list<RenderParticle*> worldParticles) {
	for (auto renderParticle : worldParticles) {
		if (renderParticle->particle->IsDestroyed()) {
			renderParticle->particle->Instantiate();

			float r = static_cast<float>(rand()) / RAND_MAX;
			float g = static_cast<float>(rand()) / RAND_MAX;
			float b = static_cast<float>(rand()) / RAND_MAX;

			renderParticle->model->setColor(Vector3(r, g, b));
			renderParticle->particle->AddForce(Vector3(0, 5000, 0));
			renderParticle->particle->setPosition(Vector3(0, -300, 0));			
		}
	}
}

void RenderParticleController::Update(float time, std::list<RenderParticle*> worldParticles) {
	/*if (this->spawnTicks >= this->spawnInterval) {
		this->OnActivate(worldParticles);
		this->spawnTicks = 0.0f;
	}
	this->spawnTicks += time;*/
}

