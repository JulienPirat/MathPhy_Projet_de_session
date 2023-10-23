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

	//ParticleContactNaïve(std::vector<Particle*> _particle, float _radius = 5);

	void Init(float deltaTime);


	//take a pointer to an array of contacts and the number of contact left to be generated;
	unsigned int addContact(ParticleContact* contact, unsigned int limit) const;
};

