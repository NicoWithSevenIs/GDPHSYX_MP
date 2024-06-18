#pragma once

#include "list"
#include "cstdlib"
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
		glm::vec3 randomizeModelColor();
		std::list<RenderParticle*> createRenderParticles();
		void OnActivate(std::list<RenderParticle*> worldParticles);

	public:
		void Update(float time, std::list<RenderParticle*> worldParticles);

};