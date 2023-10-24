#pragma once
#include "Particle.h"
#include "ParticleForceGenerator.h"
#include <vector>


class ParticleForceRegistry
{
protected:

	///Attributes

	struct ParticleForceEntry {
		Particle* particle;
		ParticleForceGenerator* forceGenerator;
	};

	using Registry = std::vector<ParticleForceEntry>;
	Registry m_registery;

public:

	///Methodes

	/**
	* Registers the given force generator to apply to the
	* given particle.
	*/
	void add(Particle* particle, ParticleForceGenerator* fg);

	/**
	* Removes the given registered pair from the registry.
	* If the pair is not registered, this method will have
	* no effect.
	*/
	void remove(Particle* particle, ParticleForceGenerator* fg);

	/**
	* Clears all registrations from the registry. This will
	* not delete the particles or the force generators
	* themselves, just the records of their connection.
	*/
	void clear();

	/**
	* Calls all the force generators to update the forces of
	* their corresponding particles.
	*/
	void UpdateForce(float duration);

};

