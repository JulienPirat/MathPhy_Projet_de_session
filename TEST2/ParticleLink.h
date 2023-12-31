#pragma once
#include <ParticleContactGenerator.h>

class ParticleLink : public	ParticleContactGenerator
{
	protected:

		///Attributes

		//Linked Particles
		Particle* particle[2];

	public:

		///Methodes

		//return the length of the link
		float currentLength() const;

		//Take a pointer to an array of contacts and the number of contact left to be generated
		unsigned int addContact(ParticleContactRegistry* ContactRegistry, unsigned int limit) const = 0;

};

