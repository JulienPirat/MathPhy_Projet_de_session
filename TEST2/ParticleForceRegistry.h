#pragma once
#include "Particle.h"
#include "ParticleForceGenerator.h"
#include <vector>


class ParticleForceRegistry
{
private:
	struct ParticleForceEntry {
		Particle* particle;
		ParticleForceGenerator* forceGenerator;
	};

	using Registry = std::vector<ParticleForceGenerator>;
	Registry m_registery;

public:
	//Registry Accessor
	void UpdateForce(float duration);
};

