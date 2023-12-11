#include "RBContactResolver.h"

void RBContactResolver::resolveContacts(RBContactRegistry* ContactRegistry, unsigned int numContact, float duration)
{
	iterationsUsed = 0;
	while (iterationsUsed < iteration)
	{
		//R�soudre en premier le contact qui a l'interp�n�tration la plus grande
		// Avoir une liste de contacts tri�s par ordre d'interp�n�tration du plus grand au plus petit
		// Ensuite , r�soudre le contact qui a la plus grande interp�n�tration
		// Updater la p�n�tration de chaque contact car ils ont peut-�tre boug�
		// Page 367

		/// R�soudre l'interp�n�tration
		float maxInterpenetration = 0;
		RBContact* contactToResolveInterpenatration = nullptr;

		for (RBContact contact : ContactRegistry->contacts)
		{
			if (contact.penetration > maxInterpenetration) 
			{
				maxInterpenetration = contact.penetration;
				contactToResolveInterpenatration = &contact;
			}
		}

		if (contactToResolveInterpenatration != nullptr)
		{
			contactToResolveInterpenatration->resolveInterpenetration(duration);
		}


		/// Ajouter l'impulsion
		float maxClosingVelocity = ContactRegistry->contacts[0].calculateClosingVelocity();
		RBContact* contactApplyImpulse = &ContactRegistry->contacts[0];

		for (RBContact contact : ContactRegistry->contacts)
		{
			if (contact.calculateClosingVelocity() < maxClosingVelocity)
			{
				maxClosingVelocity = contact.calculateClosingVelocity();
				contactApplyImpulse = &contact;
			}
		}

		contactApplyImpulse->AddImpulse(duration);
		iterationsUsed++;
	}
}