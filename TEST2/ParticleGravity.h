#pragma once
#include "Vector3D.h"
#include <ParticleForceGenerator.h>

class ParticleGravity : public ParticleForceGenerator
{
private:

	/// Attributs

	Vector3D m_gravity;

public:

	///Methodes

	//Rappel Force = particle->GetMass() * m_gravity
	void UpdateForce(Particle* particle, float duration);
};

