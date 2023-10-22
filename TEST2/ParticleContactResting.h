#pragma once
#include "ParticleContactGenerator.h"
#include <vector>

class ParticleContactResting : public ParticleContactGenerator
{
	void Init(float deltaTime);

	//Radius du mur
	float radius;

	//Particles qui pourraient collisioner avec le sol
	std::vector<Particle*> particle;
};

