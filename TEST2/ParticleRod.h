#pragma once
#include <ParticleLink.h>

class ParticleRod : public ParticleLink
{
public:

	///Attributs

	//a contact will be generated if the distance between particles is not equals to length
	float length;

	///Constructeur

	ParticleRod(float len, Particle* part1, Particle* part2) {
		length = len;
		particle[0] = part1;
		particle[1] = part2;
	}

	///Methodes

	//Returns the current length of the cable.
	float currentLength() const;

	//Fill ParticleContact with information from particles and contact generator
	//Contact is different wether the distance is shorter or greater than the length
	unsigned int addContact(ParticleContactRegistry* ContactRegistry, unsigned int limit)const;
};

