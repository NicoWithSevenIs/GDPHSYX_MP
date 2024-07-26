#pragma once

#include "../Forces/ForceGenerator.hpp"

class ParticleSpring: public ForceGenerator
{

private:
	Particle* other;
	float springConstant;
	float restLength;

public:
	ParticleSpring(Particle* other, float springConstant, float restLength) :
		other(other), springConstant(springConstant), restLength(restLength) {}

	void UpdateForce(Particle* p, float deltaTime) override;

};

