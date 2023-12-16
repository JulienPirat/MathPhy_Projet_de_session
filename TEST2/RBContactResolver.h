#pragma once
#include <RBContactRegistry.h>

class RBContactResolver
{
protected:

	///Attributes

	//number of allowed iterations
	unsigned int maxIteration;

	//Track the number of iterations used
	unsigned int iterationsUsed;

public:

	///Methodes

	//Creates a new contact resolver with the number of max iterations
	RBContactResolver() { maxIteration = 50; };
	RBContactResolver(unsigned iterations) : maxIteration(iterations) {};

	void resolveContacts(RBContactRegistry* ContactRegistry, unsigned int numContact, float duration, std::vector<std::pair<RigidBody*, RigidBody*>> potentialCollision);

	void setIterations(unsigned iterations) { maxIteration = iterations; };
};