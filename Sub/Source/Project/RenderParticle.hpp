#pragma once

#include "Particle.hpp"
#include "Model.h"
#include "Managers/ShaderManager.hpp"

using namespace managers;
class RenderParticle
{
	public:
		std::string name;
		Particle* particle;
		Model* model;
		float timeTravelled = 0;

	public:
		RenderParticle(std::string name, Model* m, Particle* p ): name(name), model(m), particle(p) {
			this->model->assignShader((*ShaderManager::getInstance())[ShaderNames::MODEL_SHADER]);
			this->model->transform.scale = Vector3::one * particle->radius;
		}

		void Draw();

};