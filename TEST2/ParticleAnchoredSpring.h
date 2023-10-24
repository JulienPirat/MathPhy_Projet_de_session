#pragma once
#include <ParticleForceGenerator.h>

class ParticleAnchoredSpring : public ParticleForceGenerator
{
private:

	///Attributes

	//Other Anchor
	Vector3D m_anchor;

	//Spring Constant
	float m_k;
	float m_restLength;

public:

	///Constructeur

	ParticleAnchoredSpring(Vector3D anchor, float k, float restLength) {
		m_k = k;
		m_restLength = restLength;
		m_anchor = anchor;
	}

	///Methodes

	//apply simplified drag based on particle velocity
	void UpdateForce(Particle* particle, float duration);
};

