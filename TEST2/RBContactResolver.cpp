#include "RBContactResolver.h"

void RBContactResolver::resolveContacts(RBContactRegistry* ContactRegistry, unsigned int numContact, float duration)
{
	iterationsUsed = 0;

	bool shouldStop = iterationsUsed < maxIteration;

	while (!shouldStop)
	{
		//R�soudre en premier le contact qui a l'interp�n�tration la plus grande
		// Avoir une liste de contacts tri�s par ordre d'interp�n�tration du plus grand au plus petit
		// Ensuite , r�soudre le contact qui a la plus grande interp�n�tration
		// Updater la p�n�tration de chaque contact car ils ont peut-�tre boug�
		// Page 367

		/// R�soudre l'interp�n�tration
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
