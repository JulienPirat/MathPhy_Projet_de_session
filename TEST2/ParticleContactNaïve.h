#pragma once
#include <vector>
#include <Particle.h>
#include "ParticleContactGenerator.h"
#include <list>

class ParticleContactNa´ve : public ParticleContactGenerator
{

public :
	//ParticleContactNa´ve(std::vector<Particle*> _particle, float _radius = 5);

	void Init(float deltaTime);

	//Radius de la particule
	float radius;
	
	//Particles qui pourraient collisioner ensemble
	std::vector<Particle*> particle;

	//take a pointer to an array of contacts and the number of contact left to be generated;
	unsigned int addContact(ParticleContact* contact, unsigned int limit) const;
};

