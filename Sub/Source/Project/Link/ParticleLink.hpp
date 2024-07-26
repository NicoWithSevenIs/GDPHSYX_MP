#pragma once

#include "../Particle.hpp"
#include "../ParticleContact.hpp"


class ParticleLink
{
	public: 
		Particle* particles[2];

		inline virtual ParticleContact* getContact() { return nullptr;}

	protected:
		float currentLength();

};

