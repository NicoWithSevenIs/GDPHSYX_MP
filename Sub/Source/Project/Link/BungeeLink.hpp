#pragma once

#include "../Vector3.hpp"
#include "../Particle.hpp"
#include "ParticleLink.hpp"
#include "../Forces/ForceGenerator.hpp"


/*


*/
class BungeeLink: public ForceGenerator
{
	private:
		Vector3 anchorPoint;
		float springConstant;
		float restLength;

		float a = 0;

		float maxLength = 300;

	public:
		BungeeLink(Vector3 pos, float springConstant, float restLength) :
			anchorPoint(pos), springConstant(springConstant), restLength(restLength) {}

		void UpdateForce(Particle* p, float deltaTime) override;



};

