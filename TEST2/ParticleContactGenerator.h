#pragma once
#include <ParticleContact.h>

class ParticleContactGenerator
{
public:
	//take a pointer to an array of contacts and the number of contact left to be generated
	virtual unsigned int addContact(ParticleContact* contact, unsigned int limit) const = 0;
};

