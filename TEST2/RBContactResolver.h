#pragma once
#include <RBContactRegistry.h>

class RBContactResolver
{
protected:

	///Attributes

	//number of allowed iterations
	unsigned int maxIteration;

	

public:

	//Track the number of iterations used
	unsigned int iterationsUsed = 0;

	///Methodes


	//Creates a new contact resolver with the number of max iterations
	RBContactResolver() { maxIteration = 50; };
	RBContactResolver(unsigned iterations) : maxIteration(iterations) {};

	void resolveContacts(RBContactRegistry* ContactRegistry, unsigned int numContact, float duration);

	void setIterations(unsigned iterations) { maxIteration = iterations; };
};