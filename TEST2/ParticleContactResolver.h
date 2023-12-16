#pragma once
#include <ParticleContact.h>
#include <ParticleContactRegistry.h>

class ParticleContactResolver
{
protected:

	///Attributes

	//number of allowed iterations
	unsigned int iteration;

	//Track the number of iterations used
	unsigned int iterationsUsed = 0;

public: 

	///Methodes

	//Creates a new contact resolver with the number of max iterations
	ParticleContactResolver() { iteration = 1; };
	ParticleContactResolver(unsigned iterations) : iteration(iterations) {};

	//take an array of contact
	//iterate on each contact according to their separatingVelocity
	//Stop when all contacts are solved or when max iterations is reached
	void resolveContacts(ParticleContactRegistry* ContactRegistry, unsigned int numContact, float duration);

	void setIterations(unsigned iterations) { iteration = iterations; };
};

