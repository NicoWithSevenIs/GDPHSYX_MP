#include "RenderParticleController.hpp"

RenderParticleController::RenderParticleController(int size) {
	this->size = size;
	this->spawnInterval = 5.0f;
	this->spawnTicks = 0.0f;
}

glm::vec3 RenderParticleController::randomizeModelColor() {
	
	int upperbound = 1;
	int lowerbound = 0;
	float r = rand() % (upperbound - lowerbound) + 1;
	float g = rand() % (upperbound - lowerbound) + 1;
	float b = rand() % (upperbound - lowerbound) + 1;
	glm::vec3 color = glm::vec3(r, g, b);
	return color;
}

std::list<RenderParticle*> RenderParticleController::createRenderParticles() {
	std::list<RenderParticle*> spawnedParticles = std::list<RenderParticle*>();
	int upperbound = 1;
	int lowerbound = 0;

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

		//glm::vec3 color = this->randomizeModelColor();
		
		

		renderParticle->model->transform.scale = Vector3(10, 10, 10);
		spawnedParticles.push_back(renderParticle);
	}
	return spawnedParticles;
}

void RenderParticleController::OnActivate(std::list<RenderParticle*> worldParticles) {
	for (auto renderParticle : worldParticles) {
		if (renderParticle->particle->IsDestroyed()) {
			renderParticle->particle->Instantiate();
			renderParticle->particle->setPosition(Vector3(0, -300, 0));
			//renderParticle->model->setColor(this->randomizeModelColor());
		}
	}
}

void RenderParticleController::Update(float time, std::list<RenderParticle*> worldParticles) {
	if (this->spawnTicks >= this->spawnInterval) {
		this->OnActivate(worldParticles);
		this->spawnTicks = 0.0f;
	}
	this->spawnTicks += time;
}

