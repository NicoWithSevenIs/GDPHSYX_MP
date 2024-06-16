#include "World.hpp"


void World::Update(float deltaTime) {
	//this->UpdateParticleList();
	forceRegistry.UpdateForces(deltaTime);

	for (auto p : particleList) {

		if(p->particle->IsDestroyed())
			continue;
		
		p->particle->Update(deltaTime);
		p->timeTravelled += deltaTime;


		std::cout << p->name << ": " << Vector3::Distance(p->particle->getPosition(), Vector3::zero) <<std::endl;
		if (Vector3::Distance(p->particle->getPosition(), Vector3::zero) <= 3.f) {
			this->rankings.push_back(p);
			p->particle->Destroy();
		}	

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

void World::printRankData(RenderParticle* p, int rank) {
	
	std::cout << p->name + ": " + this->getRankingText(rank) << std::endl;
	std::cout << "Mag. of Velocity: " << p->particle->getVelocity().Magnitude() << "m/s" << std::endl;

	Vector3 aveVelocity = p->particle->getVelocity() + p->particle->getInitialVelocity();
	aveVelocity *= 1/p->timeTravelled;

	std::cout << "Average Velocity: " << aveVelocity << " m/s" << std::endl;
	std::cout << p->timeTravelled << " secs\n" << std::endl;
}


void World::printResults() {
	system("cls");
	std::cout << std::fixed << std::setprecision(2);
	for (int i = 0; i < this->rankings.size(); i++) 
		printRankData(this->rankings[i], i+1);
}

bool World::allInCenter() {
	bool inCenter = true;

	for(auto p: this->particleList)
		if(!p->particle->IsDestroyed())
			inCenter = false;

	return inCenter;
}