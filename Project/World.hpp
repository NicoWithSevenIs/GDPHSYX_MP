#pragma once

#include "RenderParticle.hpp"
#include "Forces/ForceRegistry.hpp"
#include "Forces/GravityForceGenerator.hpp"

#include <list>
#include <functional>
#include <iomanip>

class World {
	
	public:
		ForceRegistry forceRegistry;
		GravityForceGenerator gravity;

	private:
		std::list<RenderParticle*> particleList;
		std::vector<RenderParticle*> rankings;

	public:
		void AddParticle(RenderParticle* p);
		void Update(float deltaTime);
		void Draw();

		void printResults();
		bool allInCenter();

	private:
		void UpdateParticleList();
		std::string getRankingText(int rank);
		void printRankData(RenderParticle* p, int rank);

};