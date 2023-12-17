#pragma once
#include <RBContactRegistry.h>

class RBContactResolver
{
protected:

	///Attributes

	//number of allowed iterations
	const unsigned int maxIteration = 100;

	

public:

	//Track the number of iterations used
	unsigned int iterationsUsed = 0;

	///Methodes


	//Creates a new contact resolver with the number of max iterations
	RBContactResolver() { iterationsUsed = 0; };
	RBContactResolver(unsigned iterations) { iterationsUsed = 0; };

	void resolveContacts(RBContactRegistry* ContactRegistry, float duration);
};