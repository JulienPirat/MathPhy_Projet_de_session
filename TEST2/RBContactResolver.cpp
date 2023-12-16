#include "RBContactResolver.h"

void RBContactResolver::resolveContacts(RBContactRegistry* ContactRegistry, unsigned int numContact, float duration)
{
	iterationsUsed = 0;

	//bool shouldStop = iterationsUsed < maxIteration;

	while (iterationsUsed < maxIteration)
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
			//shouldStop = true;
		}

		if (contactToResolveInterpenatration != nullptr)
		{
			Vector3D cp = Vector3D(0, 0, 0);
			contactToResolveInterpenatration->resolveInterpenetration(duration);
			for (auto c : ContactRegistry->contacts)
			{
				cp = Vector3D(0, 0, 0);
				if (c.RigidBodies[0] == contactToResolveInterpenatration->RigidBodies[0]) {
					
					cp = c.RigidBodies[0]->rotation.produitVectoriel(c.contactPoint);
					cp += c.RigidBodies[0]->velocity; // PAs sur car pas encore faire l'impulsion
					c.penetration -= cp.produitScalaire(c.contactNormal);
					ContactRegistry->RemoveContact(c);
				}
				else if (c.RigidBodies[0] == contactToResolveInterpenatration->RigidBodies[1]) {
					cp = c.RigidBodies[1]->rotation.produitVectoriel(c.contactPoint);
					cp += c.RigidBodies[1]->velocity; // PAs sur car pas encore faire l'impulsion
					c.penetration -= cp.produitScalaire(c.contactNormal);
					ContactRegistry->RemoveContact(c);
				}
				else if(c.RigidBodies[1] == contactToResolveInterpenatration->RigidBodies[0])
				{
					cp = c.RigidBodies[0]->rotation.produitVectoriel(c.contactPoint);
					cp += c.RigidBodies[0]->velocity; // PAs sur car pas encore faire l'impulsion
					c.penetration += cp.produitScalaire(c.contactNormal);
					ContactRegistry->RemoveContact(c);
				}
				else if (c.RigidBodies[1] == contactToResolveInterpenatration->RigidBodies[1]) {
					cp = c.RigidBodies[1]->rotation.produitVectoriel(c.contactPoint);
					cp += c.RigidBodies[1]->velocity; // PAs sur car pas encore faire l'impulsion
					c.penetration += cp.produitScalaire(c.contactNormal);
					ContactRegistry->RemoveContact(c);
				}
			}
		//	ContactRegistry->RemoveContact(contactToResolveInterpenatration);
		}

		//iterationsUsed++;

		//shouldStop |= iterationsUsed >= maxIteration;
	//}

	// Updater les contacts

	//iterationsUsed = 0;

	//while (!shouldStop)
	//{
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
			//shouldStop = true;
		}

		if(contactApplyImpulse != nullptr) 
		{
			//contactApplyImpulse->AddImpulse(duration);
			// TODO : Remove Contact
			//ContactRegistry->RemoveContact(contactApplyImpulse);
		}

		iterationsUsed++;

		//shouldStop |= iterationsUsed >= maxIteration;
	}
	
}
