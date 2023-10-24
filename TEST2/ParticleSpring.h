#pragma once
#include <ParticleForceGenerator.h>

class ParticleSpring : public ParticleForceGenerator
{
private:
	//Other particle
	Particle* m_other;

	//Spring constant
	float springConstant;

	float m_restLength;

public:
	//apply simplified drag based on particle velocity
	void UpdateForce(Particle* particle, float duration);
};

