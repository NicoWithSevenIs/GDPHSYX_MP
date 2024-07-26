#include "AnchoredSpring.hpp"

void AnchoredSpring::UpdateForce(Particle* p, float deltaTime)
{

	Vector3 pos = p-> position;
	Vector3 force = pos - anchorPoint;

	float mag = force.Magnitude();

	float springForce = -springConstant * abs(mag-restLength);

	force.Normalize();
	force *= springForce;

	p->AddForce(force);

}
