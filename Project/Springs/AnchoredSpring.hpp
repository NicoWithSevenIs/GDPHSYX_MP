#pragma once

#include "../Forces/ForceGenerator.hpp"

class AnchoredSpring: public ForceGenerator
{

	public:
		Vector3 anchorPoint;
		float springConstant;
		float restLength;

	public:
		AnchoredSpring(Vector3 pos, float springConstant, float restLength):
			anchorPoint(pos), springConstant(springConstant), restLength(restLength){}

		void UpdateForce(Particle* p, float deltaTime) override;
	
};

