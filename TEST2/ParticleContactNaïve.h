#pragma once
#include <vector>
#include <Particle.h>
#include "ParticleContactGenerator.h"
#include <list>

class ParticleContactNaïve : public ParticleContactGenerator
{

public :
	//ParticleContactNaïve(std::vector<Particle*> _particle, float _radius = 5);

	void Init();

	//Radius de la particule
	float radius;
	
	//Particles qui pourraient collisioner ensemble
	std::list<Particle*> particle;

	//take a pointer to an array of contacts and the number of contact left to be generated;
	unsigned int addContact(ParticleContact* contact, unsigned int limit) const;
};

