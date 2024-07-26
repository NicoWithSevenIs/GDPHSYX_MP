#include "ChainLink.hpp"

void ChainLink::UpdateForce(Particle* p, float deltaTime)
{

	Vector3 dir = p->position - anchorPosition;
	float mag = dir.Magnitude();

	if (mag >= tetherLength) {
		p->velocity += -p->velocity;
	}
	
	
}
