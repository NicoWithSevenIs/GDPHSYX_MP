#include "ForceRegistry.hpp"

void ForceRegistry::Add(Particle* particle, ForceGenerator* generator)
{
	RegisteredForceOffender toAdd;

	toAdd.particle = particle;
	toAdd.forceGenerator = generator;


	Registry.push_back(toAdd);
	
}

void ForceRegistry::Remove(Particle* particle, ForceGenerator* generator)
{
	auto RemoveChecker = [particle, generator](RegisteredForceOffender* forceGenerator) {
		return forceGenerator->particle == particle && forceGenerator->forceGenerator == generator;
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
		i.forceGenerator->UpdateForce(i.particle, deltaTime);
	}


}
