#pragma once

#include "Vector3.hpp"
class Particle {
	
	public:
		float mass = 5;

		float lifeSpan = 0;
		float lifeTicks = 0;

	protected:
		Vector3 accumulatedForce = Vector3::zero;
		

		// 0 -> 1
		// 0 nothing left
		// 1 constant v

		float damping = 0.9f;
		bool isDestroyed = false;

	private:
		Vector3 position;
		Vector3 velocity;
		Vector3 acceleration;

		Vector3 initialVelocity;

	protected:
		void UpdatePosition(float deltaTime);
		void UpdateVelocity(float deltaTime);



	public:
		void Update(float deltaTime);
		void Instantiate();
		void Destroy();
		bool IsDestroyed();

		void AddForce(Vector3 force);
		void ResetForce();

	public: 
		void setPosition(Vector3 position);
		void setVelocity(Vector3 velocity);
		void setAcceleration(Vector3 acceleration);

	public:
		Vector3 getPosition();
		Vector3 getVelocity();
		Vector3 getInitialVelocity();

};