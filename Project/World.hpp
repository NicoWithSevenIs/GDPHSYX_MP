#pragma once

#include "RenderParticle.hpp"
#include "Forces/ForceRegistry.hpp"
#include "Forces/GravityForceGenerator.hpp"
#include "Controllers/RenderParticleController/RenderParticleController.hpp"
#include <list>
#include <functional>
#include <iomanip>

class World {
	
	public:

		ForceRegistry forceRegistry;
		GravityForceGenerator gravity;

	public:
		std::list<RenderParticle*> particleList;
		std::vector<RenderParticle*> rankings;

	public:
	
		void AddParticle(RenderParticle* p);
		void AddParticleBatch(std::list<RenderParticle*> particleBatch);
		void Update(float deltaTime);
		void Draw();

	private:
		void UpdateParticleList();


};