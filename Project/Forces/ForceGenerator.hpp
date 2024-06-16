#pragma once

#include "../Particle.hpp"

class ForceGenerator
{

	public:
		virtual void UpdateForce(Particle* p, float deltaTime){
			p->AddForce(Vector3::zero);
		}


};

