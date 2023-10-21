#pragma once
#include <ParticleLink.h>

class ParticleCable : public ParticleLink
{
	protected:
		//a contact will be generated if the distance between the particles is larger than maxLength
		float maxLength;

		//bounciness of the cable
		float restitution;

	public:
		//Fill information contact with informations from particles and contact generator
		unsigned int addContact(ParticleContact* contact, unsigned int limit) const;
};

