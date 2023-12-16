#pragma once
#include <ParticleForceGenerator.h>

class ParticleDrag: public ParticleForceGenerator
{
private:

	///Attributes

	//drag coefficient
	double m_k1;
	double m_k2;

public:

	///Constructeur

	ParticleDrag(double k1, double k2) {
		m_k1 = k1;
		m_k2 = k2;
	}

	///Methodes

	//apply Hooke's law based on particles positions
	void UpdateForce(Particle* particle, double duration);
};

