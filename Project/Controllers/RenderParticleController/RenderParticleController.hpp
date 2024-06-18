#pragma once

#include "list"
#include "cstdlib"
#include "cmath"
#include "../../RenderParticle.hpp"
#include "../../Components/Shader.hpp"
#include "../../World.hpp"

class World;

class RenderParticleController {
	private:
		int size;
		int count;
		float spawnInterval = 0.1f;
		float spawnTicks;

	public:
		RenderParticleController(int size);
	public:
		
		std::list<RenderParticle*> createRenderParticleBatch();
		RenderParticle* createRenderParticle();
		void intializeVelocities(RenderParticle* pRenderParticle);
		void initializeDirection(RenderParticle* pRenderParticle);
		void OnActivate(std::list<RenderParticle*> worldParticles);

	public:
		void tickDown(World* refWorld);

};