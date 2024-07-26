#pragma once

#include "RenderParticle.hpp"
#include "Forces/ForceRegistry.hpp"
#include "Forces/GravityForceGenerator.hpp"
#include <list>
#include <functional>
#include <iomanip>
#include "Link/ParticleLink.hpp"
#include "ParticleContact.hpp"
#include "ContactResolver.hpp"

class World {
	
	public:

		ForceRegistry forceRegistry;
		GravityForceGenerator gravity;
		ContactResolver contactResolver;
	public:
		std::list<RenderParticle*> particleList;
		std::list<ParticleLink*> linkList;
		std::vector<RenderParticle*> rankings;
		std::vector<ParticleContact*> contactList;

	public:
	
		void AddParticle(RenderParticle* p);
		void AddParticleBatch(std::list<RenderParticle*> particleBatch);
		void AddContact(Particle* p1, Particle* p2, float res, Vector3 contactNormal, float depth);
		void Update(float deltaTime);
		void Draw();

	private:
		void UpdateParticleList();

	protected:
		void GenerateContacts();
		void GetOverlaps();


};