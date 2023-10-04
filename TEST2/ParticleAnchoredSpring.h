#pragma once
#include <ParticleForceGenerator.h>

class ParticleAnchoredSpring : public ParticleForceGenerator
{
private:
	//Other Anchor
	Vector3D m_anchor;

	//Spring Constant
	float m_k;
	float m_restLength;

public:
	//apply simplified drag based on particle velocity
	void UpdateForce(Particle* particle, float duration);
};

