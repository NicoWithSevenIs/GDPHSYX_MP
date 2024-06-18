#include "RenderParticleController.hpp"

RenderParticleController::RenderParticleController(int size) {
	this->size = size;
	this->spawnInterval = 5.0f;
	this->spawnTicks = 0.0f;
}

std::list<RenderParticle*> RenderParticleController::createRenderParticleBatch() {
	std::list<RenderParticle*> spawnedParticles = std::list<RenderParticle*>();

	for (int i = 0; i < this->size; i++) {

		Shader* shader = (*ShaderManager::getInstance())[ShaderNames::MODEL_SHADER];
		Model* pModel = new Model("3D/sphere.obj");
		Particle* pParticle = new Particle();
		RenderParticle* renderParticle = new RenderParticle("Sphere", pModel, pParticle);

		float lifeSpanRand = static_cast<float>(rand()) / RAND_MAX;
		lifeSpanRand = 1.0f + lifeSpanRand * (10.0f - 1.0f + 1.0f);
		renderParticle->particle->lifeSpan = lifeSpanRand;

		float r = static_cast<float>(rand()) / RAND_MAX;
		float g = static_cast<float>(rand()) / RAND_MAX;
		float b = static_cast<float>(rand()) / RAND_MAX;

		renderParticle->model->setColor(Vector3(r, g, b));

		renderParticle->particle->setPosition(Vector3(0, -300, 0));
		renderParticle->model->assignShader(shader);

		float radius = static_cast<float>(rand()) / RAND_MAX;
		radius = 2.0f + radius * (10.0f - 2.0f + 1.0f);
		
		renderParticle->model->transform.scale = Vector3(radius, radius, radius);

		this->intializeVelocities(renderParticle);
		spawnedParticles.push_back(renderParticle);
	}
	return spawnedParticles;
}

RenderParticle* RenderParticleController::createRenderParticle() {

	Shader* shader = (*ShaderManager::getInstance())[ShaderNames::MODEL_SHADER];
	Model* pModel = new Model("3D/sphere.obj");
	Particle* pParticle = new Particle();
	RenderParticle* renderParticle = new RenderParticle("Sphere", pModel, pParticle);

	float lifeSpanRand = static_cast<float>(rand()) / RAND_MAX;
	lifeSpanRand = 1.0f + lifeSpanRand * (10.0f - 1.0f + 1.0f);
	renderParticle->particle->lifeSpan = lifeSpanRand;

	float r = static_cast<float>(rand()) / RAND_MAX;
	float g = static_cast<float>(rand()) / RAND_MAX;
	float b = static_cast<float>(rand()) / RAND_MAX;

	renderParticle->model->setColor(Vector3(r, g, b));

	renderParticle->particle->setPosition(Vector3(0, -300, 0));
	renderParticle->model->assignShader(shader);

	float radius = static_cast<float>(rand()) / RAND_MAX;
	radius = 2.0f + radius * (10.0f - 2.0f + 1.0f);
	radius = 10.0f;

	renderParticle->model->transform.scale = Vector3(radius, radius, radius);
	this->intializeVelocities(renderParticle);
	return renderParticle;
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
	pRenderParticle->particle->setVelocity(Vector3(vX, vY, vZ));
	this->initializeDirection(pRenderParticle);
	
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

void RenderParticleController::OnActivate(std::list<RenderParticle*> worldParticles) {
	for (auto renderParticle : worldParticles) {
		if (renderParticle->particle->IsDestroyed()) {
			renderParticle->particle->Instantiate();

			float r = static_cast<float>(rand()) / RAND_MAX;
			float g = static_cast<float>(rand()) / RAND_MAX;
			float b = static_cast<float>(rand()) / RAND_MAX;

			renderParticle->model->setColor(Vector3(r, g, b));
			renderParticle->particle->AddForce(Vector3(0, 9000, 0));
			renderParticle->particle->setPosition(Vector3(0, -300, 0));			
		}
	}
}

void RenderParticleController::tickDown(float time) {

}

