#pragma once

#include "ForceGenerator.hpp"
#include <list>
#include <functional>

class ForceRegistry
{
		public:
			void Add(Particle* particle, ForceGenerator* generator);
			void Remove(Particle* particle, ForceGenerator* generator);
			void Clear();

			void UpdateForces(float deltaTime);

		protected:
			struct RegisteredForceOffender {
				Particle* particle;
				ForceGenerator* forceGenerator;
			};

			std::list<RegisteredForceOffender> Registry;
	
};

