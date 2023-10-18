#pragma once
#include <vector>
#include <Particle.h>
#include "ParticleContactGenerator.h"

class ParticleContactNaïve : public ParticleContactGenerator
{
	//Radius de la particule
	float radius;
	
	//Particles qui pourraient collisioner ensemble
	std::vector<Particle*> particle;

	//take a pointer to an array of contacts and the number of contact left to be generated
	virtual unsigned int addContact(ParticleContact* contact, unsigned int limit) const;
};

