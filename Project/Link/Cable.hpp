#pragma once


#include "../Link/ParticleLink.hpp"
#include "../Vector3.hpp"
#include "../Particle.hpp"

class Cable: public ParticleLink
{

	public:	
		float cableLength;
		float restitution = 0;

	private:

		ParticleContact* getContact() override;

};

