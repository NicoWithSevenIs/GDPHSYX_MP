#pragma once

#include "../Springs/ParticleSpring.hpp"
#include "../Link/Cable.hpp"
#include "../Particle.hpp"
#include "vector"
#include "unordered_map"

struct CableSet {
	std::vector<Particle*> particles;
	std::vector<Cable*> cables;
};


class CableCreator {

private:
	float cableLength;
	float particleGap;
	float particleRadius;


	
	Vector3 forceToApply;

public:

	Particle* leftMost = nullptr;

	inline CableCreator(float cableLength, float particleGap, float particleRadius, Vector3 forceToApply):
	cableLength(cableLength), particleGap(particleGap), forceToApply(forceToApply){}



public:
	CableSet createCables();

	int setXOffset(int i);

};