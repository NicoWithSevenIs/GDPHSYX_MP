#pragma once

#include "ForceGenerator.hpp"
#include <list>
#include <functional>

class ForceRegistry {
public:
	void Add(Particle* particle, ForceGenerator* generator);
	void Remove(Particle* particle, ForceGenerator* generator);
	void Clear();

	void UpdateForces(float time);

protected:
	struct ParticleForceRegistry {
		Particle* particle;
		ForceGenerator* generator;
	};

	std::list<ParticleForceRegistry> Registry;
};

