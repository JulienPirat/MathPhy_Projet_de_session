#pragma once
#include <ParticleForceGenerator.h>

class ParticleDrag: public ParticleForceGenerator
{
private:
	//Other particle
	Particle* m_other;

	//Spring constant
	float m_k;

	float m_restLength;

public:
	//apply Hooke's law based on particles positions
	void UpdateForce(Particle* particle, float duration);
};

