#pragma once

#include "Particle.hpp"
#include "Vector3.hpp"

class ParticleContact
{
	
		public:
			Particle* particles[2];
			float restitution;

			Vector3 contactNormal;

			void resolve(float deltaTime);

		protected:
			float getSeparatingSpeed();
			void resolveVelocity(float deltaTime);

};

