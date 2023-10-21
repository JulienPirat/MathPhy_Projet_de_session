#pragma once
#include <ParticleContact.h>

class ParticleContactResolver
{
protected:
	//number of allowed iterations
	unsigned int iteration;

	//Track the number of iterations used
	unsigned iterationsUsed;

public: 
	//Creates a new contact resolver with the number of max iterations
	ParticleContactResolver(unsigned iterations) : iteration(iterations) {};

	//take an array of contact
	//iterate on each contact according to their separatingVelocity
	//Stop when all contacts are solved or when max iterations is reached
	void resolveContacts(ParticleContact* contactArray, unsigned int numContact, float duration);

	void setIterations(unsigned iterations) { iteration = iterations; };
};

