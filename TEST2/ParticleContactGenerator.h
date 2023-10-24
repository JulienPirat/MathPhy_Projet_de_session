#pragma once
#include <ParticleContact.h>
#include <ParticleContactRegistry.h>

class ParticleContactGenerator
{
public:

	///Methodes

	//take a pointer to an array of contacts and the number of contact left to be generated
	virtual unsigned int addContact(ParticleContactRegistry* ContactRegistry , unsigned int limit) const = 0;
};

