#include "RBContactResolver.h"

void RBContactResolver::resolveContacts(RBContactRegistry* ContactRegistry, unsigned int numContact, float duration)
{
	iterationsUsed = 0;

	bool shouldStop = iterationsUsed < maxIteration;

	while (!shouldStop)
	{
		//Résoudre en premier le contact qui a l'interpénétration la plus grande
		// Avoir une liste de contacts triés par ordre d'interpénétration du plus grand au plus petit
		// Ensuite , résoudre le contact qui a la plus grande interpénétration
		// Updater la pénétration de chaque contact car ils ont peut-être bougé
		// Page 367

		/// Résoudre l'interpénétration
		float maxInterpenetration = 0;
		RBContact* contactToResolveInterpenatration = nullptr;

		if(!ContactRegistry->contacts.empty())
		{
			for (RBContact contact : ContactRegistry->contacts)
			{
				if (contact.penetration > maxInterpenetration)
				{
					maxInterpenetration = contact.penetration;
					contactToResolveInterpenatration = &contact;
				}
			}
		}
		else
		{
			shouldStop = true;
		}

		if (contactToResolveInterpenatration != nullptr)
		{
			contactToResolveInterpenatration->resolveInterpenetration(duration);
			ContactRegistry->RemoveContact(contactToResolveInterpenatration);
		}

		iterationsUsed++;

		shouldStop |= iterationsUsed >= maxIteration;
	}

	// Updater les contacts

	iterationsUsed = 0;

	while (!shouldStop)
	{
		/// Ajouter l'impulsion
		float maxClosingVelocity = ContactRegistry->contacts[0].calculateClosingVelocity();
		RBContact* contactApplyImpulse = &ContactRegistry->contacts[0];

		if (!ContactRegistry->contacts.empty())
		{
			for (RBContact contact : ContactRegistry->contacts)
			{
				if (contact.calculateClosingVelocity() < maxClosingVelocity)
				{
					maxClosingVelocity = contact.calculateClosingVelocity();
					contactApplyImpulse = &contact;
				}
			}
		}
		else {
			shouldStop = true;
		}

		if(contactApplyImpulse != nullptr) 
		{
			contactApplyImpulse->AddImpulse(duration);
			ContactRegistry->RemoveContact(contactApplyImpulse);
		}

		iterationsUsed++;

		shouldStop |= iterationsUsed >= maxIteration;
	}
	
}
