#pragma once
#include <ParticleForceGenerator.h>

class ParticleBuoyancy : public ParticleForceGenerator
{
private:


	///Attributes

	//Particle properties
	double m_maxDepth;
	double m_volume;

	//Effect properties
	double m_waterHeight;
	double liquidDensity;

public:

	///Constructeur

	ParticleBuoyancy(double maxDepth, double volume, double waterHeight, double liquidDens) {
		m_maxDepth = maxDepth;
		m_volume = volume;
		m_waterHeight = waterHeight;
		liquidDensity = liquidDens;
	}

	///Methodes

	//apply simplified drag based on particle velocity
	void UpdateForce(Particle* particle, double duration);
};

