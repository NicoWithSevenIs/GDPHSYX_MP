#include "DragForceGenerator.hpp"

DragForceGenerator::DragForceGenerator(){}

DragForceGenerator::DragForceGenerator(float _k1, float _k2): k1(_k1), k2(_k2) {}

void DragForceGenerator::UpdateForce(Particle* p, float deltaTime)
{
	
	Vector3 force = Vector3::zero;
	Vector3 currV = p->velocity;

	float mag = currV.Magnitude();

	if(mag <= 0)
		return;

	float dragForce = (this->k1 * mag) + (this->k2 * mag);

	Vector3 dir = Vector3::Normalized(currV);

	p->AddForce(dir * -dragForce);

}
