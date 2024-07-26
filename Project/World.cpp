#include "World.hpp"


void World::Update(float deltaTime) {
	//this->UpdateParticleList();
	forceRegistry.UpdateForces(deltaTime);

	for (auto p : particleList) {
		
		p->particle->Update(deltaTime);
		p->timeTravelled += deltaTime;
		
	}
		
}

void World::Draw() {

	for (auto p : particleList)
		p->Draw();
}

void World::AddParticle(RenderParticle* p) {
	this->particleList.push_back(p);

	//forceRegistry.Add(p->particle, &gravity);
}

void World::AddParticleBatch(std::list<RenderParticle*> particleBatch) {
	for (auto spawnedParticle : particleBatch) {
		this->particleList.push_back(spawnedParticle);
	}
}

void World::UpdateParticleList() {

	auto removeCheck = [](RenderParticle* p) {
		return p->particle->IsDestroyed();
	};

	this->particleList.remove_if(removeCheck);

}


