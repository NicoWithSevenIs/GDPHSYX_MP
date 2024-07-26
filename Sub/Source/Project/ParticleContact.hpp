#pragma once

#include "Particle.hpp"
#include "Vector3.hpp"

class ParticleContact
{
	
		public:

			float depth;



			Particle* particles[2];
			float restitution;

			Vector3 contactNormal;

			void resolve(float deltaTime);

		protected:
			void resolveInterpenetration(float deltaTime);

			
			void resolveVelocity(float deltaTime);

		public:
			float getSeparatingSpeed();

};

