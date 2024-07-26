#pragma once

#include "ParticleContact.hpp"
#include <Vector>
#include <algorithm>
#include <functional>

class ContactResolver
{
	private:
		float max_iter;

	public:
		ContactResolver(float _max_iter = 20): max_iter(_max_iter){}
	
	public:
		void Resolve(std::vector<ParticleContact*> contactList, float deltaTime);

	
};

