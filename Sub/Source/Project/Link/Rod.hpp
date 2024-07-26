#pragma once


#include "ParticleLink.hpp"


class Rod: public ParticleLink
{

	public:
		float length = 1;

		float restitution = 0;

	private:
		ParticleContact* getContact() override;

};

