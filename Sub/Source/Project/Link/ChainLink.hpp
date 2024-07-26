#pragma once



#include "../Vector3.hpp"
#include "../Particle.hpp"
#include "ParticleLink.hpp"
#include "../Forces/ForceGenerator.hpp"


/*
	Well based on the gif, it looks like the link's more of a tether with a maximum distance.
	Also chains cannot stretch.
	Based on newton's third law of motion (methinks), the chain should act against the pull of gravity should
	it exceed the ano, the chain's maximum length.


*/
class ChainLink: public ForceGenerator
{


	public:
		Vector3 anchorPosition;
		Particle* particle;
		float tetherLength;

		ChainLink(Vector3 anchorPosition, Particle* particle, float tetherLength = 50):
		anchorPosition(anchorPosition), particle(particle), tetherLength(tetherLength)
		{}


		void UpdateForce(Particle* p, float deltaTime) override;

};

