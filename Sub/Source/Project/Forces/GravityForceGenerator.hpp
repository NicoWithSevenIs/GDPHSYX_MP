#pragma once

#include "ForceGenerator.hpp"

class GravityForceGenerator: public ForceGenerator
{

	private:
		Vector3 Gravity = Vector3(0, -9.81f, 0);

	public:
		GravityForceGenerator(const Vector3 gravity = Vector3(0, -9.81f, 0));
		void UpdateForce(Particle* p, float deltaTime) override;
};

