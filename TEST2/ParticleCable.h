#pragma once
#include <ParticleLink.h>

class ParticleCable : public ParticleLink
{
	protected:

		///Attributs

		//a contact will be generated if the distance between the particles is larger than maxLength
		float maxLength;

		//bounciness of the cable
		float restitution;

	public:

		///Methodes

		//Fill information contact with informations from particles and contact generator
		unsigned int addContact(ParticleContactRegistry* ContactRegistry, unsigned int limit) const;

};

