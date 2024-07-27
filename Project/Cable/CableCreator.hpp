#pragma once

#include "../Springs/ParticleSpring.hpp"
#include "../Springs/AnchoredSpring.hpp"
#include "../Particle.hpp"
#include "vector"
#include "unordered_map"

class CableCreator {
public:
	float cableLength = 0;
	float particleGap = 0;
	float particleRadius = 0;
	float gravityStrength = 0;
	Vector3 forceToApply = Vector3();

public:
	std::vector<AnchoredSpring*> anchoredSprings;
	std::vector<Particle*> particles;
	
public:
	void testPrint();
	void createCable();

};