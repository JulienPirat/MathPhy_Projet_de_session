#pragma once
#include <ParticleForceGenerator.h>

class ParticleBuoyancy : public ParticleForceGenerator
{
private:

	///Attributes

	//Particle properties
	float m_maxDepth;
	float m_volume;

	//Effect properties
	float m_waterHeight;
	float liquidDensity;

public:

	///Methodes

	//apply simplified drag based on particle velocity
	void UpdateForce(Particle* particle, float duration);
};

