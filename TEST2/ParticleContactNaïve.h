#pragma once
#include <vector>
#include <Particle.h>
#include "ParticleContactGenerator.h"
#include <list>

class ParticleContactNaïve : public ParticleContactGenerator
{

public :

	///Attributs

	//Radius de la particule
	float radius;

	//Particles qui pourraient collisioner ensemble
	std::vector<Particle*> particle;

	///Methodes

	//take a pointer to an array of contacts and the number of contact left to be generated;
	unsigned int addContact(ParticleContactRegistry* ContactRegistry, unsigned int limit) const;
};

