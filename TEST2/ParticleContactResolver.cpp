#include "ParticleContactResolver.h"

void ParticleContactResolver::resolveContacts(ParticleContact* contactArray, unsigned int numContact, float duration)
{
	iterationsUsed = 0;
	while (iterationsUsed < iteration)
	{
		//Find the contact with the largest closing velocity
		float max = 0;
		unsigned int maxIndex = numContact;
		for (unsigned int i = 0; i < numContact; i++)
		{
			float sepVel = contactArray[i].calculateSeparatingVelocity();
			if (sepVel < max && (sepVel < 0 || contactArray[i].penetration > 0))
			{
				max = sepVel;
				maxIndex = i;
			}
		}

		//Resolve this contact
		contactArray[maxIndex].resolve(duration);

		iterationsUsed++;
	}
}
