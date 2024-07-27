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

}