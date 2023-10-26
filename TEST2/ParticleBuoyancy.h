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

	///Constructeur

	ParticleBuoyancy(float maxDepth, float volume, float waterHeight, float liquidDens) {
		m_maxDepth = maxDepth;
		m_volume = volume;
		m_waterHeight = waterHeight;
		liquidDensity = liquidDens;
	}

	///Methodes

	//apply simplified drag based on particle velocity
	void UpdateForce(Particle* particle, float duration);
};

