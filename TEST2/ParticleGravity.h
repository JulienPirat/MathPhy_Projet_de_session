#pragma once
#include "Vector3D.h"
#include <ParticleForceGenerator.h>

class ParticleGravity : public ParticleForceGenerator
{
private:
	Vector3D m_gravity;
public:
	//Rappel Force = particle->GetMass() * m_gravity
	void UpdateForce(Particle* particle, float duration);
};

