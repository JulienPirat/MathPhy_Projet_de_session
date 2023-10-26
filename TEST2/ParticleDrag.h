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

	///Constructeur

	ParticleDrag(float k1, float k2) {
		m_k1 = k1;
		m_k2 = k2;
	}

	///Methodes

	//apply Hooke's law based on particles positions
	void UpdateForce(Particle* particle, float duration);
};

