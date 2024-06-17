#include "World.hpp"


void World::Update(float deltaTime) {
	//this->UpdateParticleList();
	forceRegistry.UpdateForces(deltaTime);

	for (auto p : particleList) {

		if(p->particle->IsDestroyed())
			continue;
		
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

	forceRegistry.Add(p->particle, &gravity);
}

void World::UpdateParticleList() {

	auto removeCheck = [](RenderParticle* p) {
		return p->particle->IsDestroyed();
	};

	this->particleList.remove_if(removeCheck);

}

std::string World::getRankingText(int rank) {
	
	int ones = rank % 10;

	std::string rankText;
	switch (ones) {
		case 1: rankText = "st"; break;
		case 2: rankText = "nd"; break;
		case 3: rankText = "rd"; break;
		default: rankText = "th"; break;
	}

	return std::to_string(ones) + rankText;

}

