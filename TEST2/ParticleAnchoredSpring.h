#pragma once
#include <ParticleForceGenerator.h>

class ParticleAnchoredSpring : public ParticleForceGenerator
{
private:

	///Attributes

	//Other Anchor
	Vector3D m_anchor;

	//Spring Constant
	double m_k;
	double m_restLength;

public:

	///Constructeur

	ParticleAnchoredSpring(Vector3D anchor, double k, double restLength) {
		m_k = k;
		m_restLength = restLength;
		m_anchor = anchor;
	}

	///Methodes

	//apply simplified drag based on particle velocity
	void UpdateForce(Particle* particle, double duration);


};

