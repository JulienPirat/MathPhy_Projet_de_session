#pragma once
#include <RBContactRegistry.h>

class RBContactResolver
{
protected:

	///Attributes

	//number of allowed iterations
	unsigned int iteration;

	//Track the number of iterations used
	unsigned int iterationsUsed;

public:

	///Methodes

	//Creates a new contact resolver with the number of max iterations
	RBContactResolver() { iteration = 1; };
	RBContactResolver(unsigned iterations) : iteration(iterations) {};

	void resolveContacts(RBContactRegistry* ContactRegistry, unsigned int numContact, float duration);

	void setIterations(unsigned iterations) { iteration = iterations; };
};