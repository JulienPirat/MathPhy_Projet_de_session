#pragma once
#include <ParticleForceGenerator.h>

class ParticleDrag: public ParticleForceGenerator
{
private:

	///Attributes

	//drag coefficient
	float m_k1;
	float m_k2;

public:

	///Methodes

	//apply Hooke's law based on particles positions
	void UpdateForce(Particle* particle, float duration);
};

