#pragma once

#include "list"
#include "cstdlib"
#include "cmath"
#include "../../RenderParticle.hpp"
#include "../../Components/Shader.hpp"

class RenderParticleController {
	private:
		int size;
		float spawnInterval;
		float spawnTicks;
	public:
		
	public:
		RenderParticleController(int size);
	public:
		
		std::list<RenderParticle*> createRenderParticles();
		void intializeVelocities(RenderParticle* pRenderParticle);
		void initializeAcceleration(RenderParticle* pRenderParticle);
		void initializeDirection(RenderParticle* pRenderParticle);
		void OnActivate(std::list<RenderParticle*> worldParticles);

	public:
		void Update(float time, std::list<RenderParticle*> worldParticles);

};