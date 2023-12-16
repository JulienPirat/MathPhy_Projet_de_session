#include "ParticleContactResolver.h"

void ParticleContactResolver::resolveContacts(ParticleContactRegistry* ContactRegistry, unsigned int numContact, float duration)
{
	iterationsUsed = 0;
	while (iterationsUsed < iteration)
	{
		//Find the contact with the largest closing velocity
		double max = 0;
		unsigned int maxIndex = 0;
		for (unsigned int i = 0; i < numContact; i++)
		{
			double sepVel = ContactRegistry->Contacts[i].calculateSeparatingVelocity();
			if (sepVel < max && (sepVel < 0 || ContactRegistry->Contacts[i].penetration > 0))
			{
				max = sepVel;
				maxIndex = i;
			}
		}

		//Resolve this contact
		ContactRegistry->Contacts[maxIndex].resolve(duration);

		iterationsUsed++;
	}
}
