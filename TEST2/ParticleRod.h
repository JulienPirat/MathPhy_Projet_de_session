#pragma once
#include <ParticleLink.h>

class ParticleRod : public ParticleLink
{
public:

	//a contact will be generated if the distance between particles is not equals to length
	float length;

	//Fill ParticleContact with information from particles and contact generator
	//Contact is different wether the distance is shorter or greater than the length
	unsigned int addContact(ParticleContact* contact, unsigned int limit)const;
};

