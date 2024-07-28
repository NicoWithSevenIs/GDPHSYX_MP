#pragma once


#include "../Link/ParticleLink.hpp"

#include "../Vector3.hpp"
#include "../Particle.hpp"

class Cable: public ParticleLink
{

	public:	
		float cableLength;
		float restitution = 0;

		Vector3 anchorPosition;


		inline Cable(Vector3 anchorPosition, Particle* p, float cableLength): cableLength(cableLength){
			particles[0] = new Particle(); 
			particles[0]->position = anchorPosition;

			particles[1] = p;
		}

		~Cable() {
			delete particles[0];
		}

	private:

		ParticleContact* getContact() override;

	
	


};

