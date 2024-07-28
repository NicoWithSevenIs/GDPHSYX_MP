#include "CableCreator.hpp"

CableSet CableCreator::createCables() {


	CableSet cableSet; 

	for (int i = 0; i < 5; i++) {
		
		Particle* particle = new Particle();
		particle->mass = 5.0f;
		particle->lifeSpan = 100.0f;
		particle->radius = this->particleRadius;
		
		int x_offset = this->setXOffset(i);
		particle->setPosition(Vector3(x_offset, 0, 0));

		

		Cable* cable = new Cable(particle->position + Vector3::up * 50, particle, cableLength);
		std::cout << particle->position + Vector3::down * 50 << std::endl;

		cableSet.cables.push_back(cable);
		cableSet.particles.push_back(particle);

	}

	leftMost = cableSet.particles[3];
	return cableSet;
}

int CableCreator::setXOffset(int i) {
	int x_offset = 0;
	switch (i) {
		case 0:
			x_offset = 0;
			break;
		case 1:
			x_offset = 0 - ((this->particleRadius) + this->particleGap);
			break;
		case 2:
			x_offset = 0 + ((this->particleRadius) + this->particleGap);
			break;
		case 3:
			x_offset = 0 - ((this->particleRadius * 2) +  (this->particleGap * 2));
			break;
		case 4:
			x_offset = 0 + ((this->particleRadius * 2) + (this->particleGap * 2));
			break;
	}
	return x_offset;
}