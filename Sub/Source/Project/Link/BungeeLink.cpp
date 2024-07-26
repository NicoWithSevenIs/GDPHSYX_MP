#include "BungeeLink.hpp"

void BungeeLink::UpdateForce(Particle* p, float deltaTime)
{

	a += deltaTime;
	Vector3 pos = p->position;
	Vector3 force = pos - anchorPoint;

	float mag = force.Magnitude();

	
	float springForce = -springConstant * abs(mag - restLength);

	
	if(springForce > 0)
		springForce -= a;



	force.Normalize();
	force *= springForce;

	p->AddForce(force);
	

	



	


}
