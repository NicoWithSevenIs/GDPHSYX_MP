#include "RenderParticle.hpp"

void RenderParticle::Draw() {
	
	if (this->particle->IsDestroyed()) {
		return;
	}
			
	this->model->transform.translation = this->particle->position;
	this->model->Draw();
}

