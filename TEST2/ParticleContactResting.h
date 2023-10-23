#pragma once
#include "ParticleContactGenerator.h"
#include <vector>

class ParticleContactResting : public ParticleContactGenerator
{
public:

	///Atributs

	//Radius du mur
	float radius;

	//Particles qui pourraient collisioner avec le sol
	std::vector<Particle*> particle;

	///Methode

	void Init(float deltaTime);

	//take a pointer to an array of contacts and the number of contact left to be generated;
	unsigned int addContact(ParticleContact* contact, unsigned int limit) const;
};

