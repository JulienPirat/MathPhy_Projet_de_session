#pragma once
#include "Particle.h"

class ParticleForceGenerator
{
public: 

	///Methodes

	virtual void UpdateForce(Particle* particle, float duration) = 0;
};

