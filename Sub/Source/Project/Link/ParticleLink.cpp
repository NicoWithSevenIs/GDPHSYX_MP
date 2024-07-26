#include "ParticleLink.hpp"

float ParticleLink::currentLength()
{
	Vector3 ret = particles[0]->position - particles[1]->position;

	return ret.Magnitude();
}
