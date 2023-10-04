#pragma once
#include <ParticleForceGenerator.h>

class ParticleBuoyancy : public ParticleForceGenerator
{
private:
	//Particle properties
	float m_maxDepth;
	float m_volume;

	//Effect properties
	float m_waterHeight;
	float liquidDensity;

public:
	//apply simplified drag based on particle velocity
	void UpdateForce(Particle* particle, float duration);
};

