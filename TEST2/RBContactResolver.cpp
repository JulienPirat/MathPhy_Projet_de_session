#include "RBContactResolver.h"

void RBContactResolver::resolveContacts(RBContactRegistry* ContactRegistry, unsigned int numContact, float duration)
{
	iterationsUsed = 0;

	while (iterationsUsed < maxIteration)
	{
		//Résoudre en premier le contact qui a l'interpénétration la plus grande
		// Avoir une liste de contacts triés par ordre d'interpénétration du plus grand au plus petit
		// Ensuite , résoudre le contact qui a la plus grande interpénétration
		// Updater la pénétration de chaque contact car ils ont peut-être bougé
		// Page 367

		/// Résoudre l'interpénétration
		float maxInterpenetration = 0;
		int indexContactToResolve = 0;
		int indexI = 0;
		if (!ContactRegistry->contacts.empty())
		{
			for (RBContact contact : ContactRegistry->contacts)
			{
				if (contact.penetration > maxInterpenetration)
				{
					maxInterpenetration = contact.penetration;
					indexContactToResolve = indexI;
				}
				indexI++;
			}
		
			Vector3D cp = Vector3D(0, 0, 0);
			ContactRegistry->contacts[indexContactToResolve].resolveInterpenetration(duration);
			ContactRegistry->contacts[indexContactToResolve].AddImpulse(duration);
			//ContactRegistry->contacts.erase(indexContactToResolve);
			ContactRegistry->RemoveContact(ContactRegistry->contacts[indexContactToResolve]);
		}
			/*
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
			ContactRegistry->RemoveContact(contactToResolveInterpenatration);
			*/

	// Updater les contacts

		/// Ajouter l'impulsion
			/*
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

		if(contactApplyImpulse != nullptr)
		{
			//contactApplyImpulse->AddImpulse(duration);
			// TODO : Remove Contact
			//ContactRegistry->RemoveContact(contactApplyImpulse);
		}*/
			iterationsUsed++;
	}
}
