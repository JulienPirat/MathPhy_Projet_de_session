#pragma once
#include "ParticleContactGenerator.h"
#include <vector>

class ParticleContactResting : public ParticleContactGenerator
{
public:

	///Constructeur

	ParticleContactResting(float rad, std::vector<Particle*> part) {
		radius = rad;
		particle = part;
	}

	///Atributs

	//Radius du mur
	float radius;

	//Particles qui pourraient collisioner avec le sol
	std::vector<Particle*> particle;

	///Methode

	//take a pointer to an array of contacts and the number of contact left to be generated;
	unsigned int addContact(ParticleContactRegistry* ContactRegistry, unsigned int limit) const;
};

