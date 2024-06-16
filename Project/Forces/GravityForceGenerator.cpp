#include "GravityForceGenerator.hpp"

GravityForceGenerator::GravityForceGenerator(const Vector3 gravity) : Gravity(gravity) {}

void GravityForceGenerator::UpdateForce(Particle* p, float deltaTime)
{
	if(p->mass <= 0 )
		return;

	Vector3 force = Gravity * p->mass;
	p->AddForce(force);

}
