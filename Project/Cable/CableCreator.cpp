#include "CableCreator.hpp"

void CableCreator::testPrint() {
	std::cout << "[TEST PRINT - CABLE CREATOR]" << std::endl;
	std::cout << "Cable Length: " << this->cableLength << std::endl;
	std::cout << "Particle Gap: " << this->particleGap << std::endl;
	std::cout << "Particle Radius: " << this->particleRadius << std::endl;
	std::cout << "Gravity Strength: " << this->gravityStrength << std::endl;
	std::cout << "Force to apply x: " << this->forceToApply.x << std::endl;
	std::cout << "Force to apply y: " << this->forceToApply.y << std::endl;
	std::cout << "Force to apply z: " << this->forceToApply.z << std::endl;

}

void CableCreator::createCable() {
	for (int i = 0; i < 5; i++) {
		Particle* particle = new Particle();
		particle->restitution = 0.9f;
		particle->mass = 50.0f;
		particle->lifeSpan = 1000.0f;
		int x_offset = this->setXOffset(i);
		particle->setPosition(Vector3(x_offset, 0, 0));
		this->particles.push_back(particle);
	}

	for (int i = 0; i < this->particles.size(); i++) {	
		int x_offset = this->setXOffset(i);
		AnchoredSpring* as = new AnchoredSpring(Vector3(x_offset, this->cableLength, 0), 3, this->cableLength - 50.0f);
		this->anchoredSprings.push_back(as);
	}	
}

int CableCreator::setXOffset(int i) {
	int x_offset = 0;
	switch (i) {
		case 0:
			x_offset = 0;
			break;
		case 1:
			x_offset = 0 - ((this->particleRadius * 2) + this->particleGap);
			break;
		case 2:
			x_offset = 0 + ((this->particleRadius * 2) + this->particleGap);
			break;
		case 3:
			x_offset = 0 - ((this->particleRadius * 3) +  (this->particleGap * 2));
			break;
		case 4:
			x_offset = 0 + ((this->particleRadius * 3) + (this->particleGap * 2));
			break;
	}
	return x_offset;
}