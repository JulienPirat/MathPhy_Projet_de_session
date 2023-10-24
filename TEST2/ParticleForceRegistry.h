#pragma once
#include "Particle.h"
#include "ParticleForceGenerator.h"
#include <vector>


class ParticleForceRegistry
{
private:

	///Attributes

	struct ParticleForceRegistration 
	{
		Particle* particle;
		ParticleForceGenerator* forceGenerator;
	};

	using Registry = std::vector<ParticleForceRegistration>;
	Registry m_registery;

public:

	///Methodes

	//Register a force generator to a particle
	void Add(Particle* particle, ParticleForceGenerator* forceGenerator);

	//Remove a force generator from a particle
	void Remove(Particle* particle, ParticleForceGenerator* forceGenerator);

	//Clear the registry
	void Clear();

	//Registry Accessor
	void UpdateForce(float duration);

};

