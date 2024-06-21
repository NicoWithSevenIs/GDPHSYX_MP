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
		float spawnInterval;
		float spawnTicks;
	public:
		bool triggerSpawn;
	public:
		RenderParticleController(int size);


	private:
		inline float r() {
			return static_cast<float>(rand()) / RAND_MAX;
		}
		inline Vector3 getRandomVector() {
			return Vector3(r(), r(), r());
		}

	public:

		RenderParticle* createRenderParticle();
		void intializeVelocities(RenderParticle* pRenderParticle);
		void initializeAcceleration(RenderParticle* pRenderParticle);
		void initializeDirection(RenderParticle* pRenderParticle);
		
	public:
		void tickDown(World* refWorld, float deltaTime);

};