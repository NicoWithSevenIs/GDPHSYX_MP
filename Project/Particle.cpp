
#include "Particle.hpp"

void Particle::UpdatePosition(float deltaTime) {
	this->position += (velocity * deltaTime) + (this->acceleration * deltaTime * deltaTime) / 2.f;
}

void Particle::UpdateVelocity(float deltaTime) {
	this->acceleration += accumulatedForce / mass;
	this->velocity += this->acceleration * deltaTime;
	this->velocity *= powf(damping, deltaTime);
}

void Particle::Update(float deltaTime) {
	this->UpdatePosition(deltaTime);
	this->UpdateVelocity(deltaTime);

	this->ResetForce();

	if (this->lifeTicks >= this->lifeSpan) {
		this->Destroy();
	}

	this->lifeTicks += deltaTime;
}

void Particle::setPosition(Vector3 position) {
	this->position = position;
}

void Particle::setVelocity(Vector3 velocity) {
	this->velocity = velocity;
	this->initialVelocity = velocity;
}

void Particle::setAcceleration(Vector3 acceleration) {
	this->acceleration = acceleration;
}

void Particle::Instantiate() {
	this->isDestroyed = false;
}

void Particle::Destroy() {
	this->isDestroyed = true;
}

bool Particle::IsDestroyed() {
	return this->isDestroyed;
}

void Particle::AddForce(Vector3 force) {
	this->accumulatedForce += force;
}

void Particle::ResetForce() {
	this->accumulatedForce = Vector3::zero;
	this->acceleration = Vector3::zero;
}