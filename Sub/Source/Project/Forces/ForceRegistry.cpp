#include "ForceRegistry.hpp"

void ForceRegistry::Add(Particle* particle, ForceGenerator* generator)
{
	ParticleForceRegistry toAdd;

	toAdd.particle = particle;
	toAdd.generator = generator;


	Registry.push_back(toAdd);
	
}

void ForceRegistry::Remove(Particle* particle, ForceGenerator* generator)
{
	auto RemoveChecker = [particle, generator](ParticleForceRegistry forceGenerator) {
		return forceGenerator.particle == particle && forceGenerator.generator == generator;
	};

	Registry.remove_if(RemoveChecker);
}

void ForceRegistry::Clear()
{
	Registry.clear();
}

void ForceRegistry::UpdateForces(float deltaTime)
{

	for (auto i : this->Registry) {
		i.generator->UpdateForce(i.particle, deltaTime);
	}


}
