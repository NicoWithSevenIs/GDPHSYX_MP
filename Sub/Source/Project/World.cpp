#include "World.hpp"


void World::Update(float deltaTime) {
	//this->UpdateParticleList();
	forceRegistry.UpdateForces(deltaTime);

	for (auto p : particleList) {
		
		p->particle->Update(deltaTime);
		p->timeTravelled += deltaTime;
		
	}

	this->GenerateContacts();

	if (contactList.size() > 0) {
		contactResolver.Resolve(this->contactList, deltaTime);
	}
		
	
}

void World::Draw() {

	for (auto p : particleList)
		p->Draw();
}

void World::AddParticle(RenderParticle* p) {
	this->particleList.push_back(p);

	forceRegistry.Add(p->particle, &gravity);
}

void World::AddParticleBatch(std::list<RenderParticle*> particleBatch) {
	for (auto spawnedParticle : particleBatch) {
		this->particleList.push_back(spawnedParticle);
	}
}

void World::AddContact(Particle* p1, Particle* p2, float res, Vector3 contactNormal, float depth)
{
	ParticleContact* toAdd = new ParticleContact();

	toAdd->particles[0] = p1;
	toAdd->particles[1] = p2;

	toAdd->restitution = res;
	toAdd->contactNormal = contactNormal;
	toAdd->depth = depth;

	contactList.push_back(toAdd);
}

void World::UpdateParticleList() {

	auto removeCheck = [](RenderParticle* p) {
		return p->particle->IsDestroyed();
	};

	this->particleList.remove_if(removeCheck);

}

void World::GenerateContacts()
{
	
	
	contactList.clear();

	this->GetOverlaps();

	for(ParticleLink* i: linkList){
			
		ParticleContact* contact = i->getContact();
		if(contact != nullptr)
			contactList.push_back(contact);

	}


	
}

void World::GetOverlaps()
{
	for (int i = 0; i < particleList.size() - 1; i++) {

		std::list<RenderParticle*>::iterator a = std::next(particleList.begin(), i);
		Particle* p1 = (*a)->particle;

		for (int j = i+1; j < particleList.size(); j++) {
			
			std::list<RenderParticle*>::iterator b = std::next(particleList.begin(), j);
			Particle* p2 = (*b)->particle;

			Vector3 mag2Vector = p1->position - p2->position;

			float mag2 = mag2Vector.SquareMagnitude();
			float rad =  p1->radius + p2->radius;

			float rad2 = rad * rad;

			if (mag2 <= rad2) {
				Vector3 dir = Vector3::Normalized(mag2Vector);

				float r = rad2-mag2;
				float depth = sqrt(r);

				float restitution = fmin(p1->restitution, p2->restitution);

				AddContact (p1,p2, restitution ,dir, depth);
			}
		}
	}

}


