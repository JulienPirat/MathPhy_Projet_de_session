#pragma once
#include "Particle.h"

class ParticleForceGenerator
{
public: 

	///Methodes

	virtual void UpdateForce(Particle* particle, double duration) = 0;
};

