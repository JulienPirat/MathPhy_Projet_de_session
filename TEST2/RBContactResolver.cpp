#include "RBContactResolver.h"
#include <RBContactGenerator.h>

void RBContactResolver::resolveContacts(RBContactRegistry* ContactRegistry, float duration)
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
		double maxInterpenetration = 0;
		int indexContactToResolve = 0;
		int indexI = 0;
		
		if (!ContactRegistry->contacts.empty())
		{
			RBContact& contactToResolveInterpenatration = ContactRegistry->contacts[0];
			for (const RBContact& contact : ContactRegistry->contacts)
			{
				if (contact.penetration > maxInterpenetration)
				{
					maxInterpenetration = contact.penetration;
					contactToResolveInterpenatration = contact;
					indexContactToResolve = indexI;
				}
				indexI++;
			}

			Vector3D cp = Vector3D(0, 0, 0);
			ContactRegistry->contacts[indexContactToResolve].resolveInterpenetration(duration);
			ContactRegistry->contacts[indexContactToResolve].AddImpulse(duration);
			iterationsUsed++;

			RigidBody* TempRB1 = ContactRegistry->contacts[indexContactToResolve].RigidBodies[0];
			RigidBody* TempRB2 = ContactRegistry->contacts[indexContactToResolve].RigidBodies[1];

			ContactRegistry->RemoveAllContactsFromTwoRigidBodies(TempRB1, TempRB2);

			shapeRB SRB1 = TempRB1->shape; //Shape Rigidbody 1
			shapeRB SRB2 = TempRB2->shape; //Shape Rigidbody 2

			switch (SRB1)
			{
				case cuboide:
					//SRB1 CUBE
					switch (SRB2) 
					{
						case cuboide:
							RBContactGenerator::boxAndBox((PBox*)TempRB1->primitive, (PBox*)TempRB2->primitive, ContactRegistry);
							break;
						case sphere:
							RBContactGenerator::boxAndSphere((PBox*)TempRB1->primitive, (PSphere*)TempRB2->primitive, ContactRegistry);
							break;
						case plane:
							RBContactGenerator::boxAndPlane((PBox*)TempRB1->primitive, (PPlane*)TempRB2->primitive, ContactRegistry);
							break;
						default:
							break;
					}
				break;

				case sphere:
					//SRB1 SPHERE
					switch (SRB2) 
					{
						case cuboide:
							RBContactGenerator::boxAndSphere((PBox*)TempRB2->primitive, (PSphere*)TempRB1->primitive, ContactRegistry);
							break;
						case sphere:
							RBContactGenerator::sphereAndSphere((PSphere*)TempRB1->primitive, (PSphere*)TempRB2->primitive, ContactRegistry);
							break;
						case plane:
							RBContactGenerator::sphereAndPlane((PSphere*)TempRB1->primitive, (PPlane*)TempRB2->primitive, ContactRegistry);
							break;
						default:
							break;
					}
				break;

				case plane:
					//SRB1 PLANE
					switch (SRB2) 
					{
						case cuboide:
							RBContactGenerator::boxAndPlane((PBox*)TempRB2->primitive, (PPlane*)TempRB1->primitive, ContactRegistry);
							break;
						case sphere:
							RBContactGenerator::sphereAndPlane((PSphere*)TempRB2->primitive, (PPlane*)TempRB1->primitive, ContactRegistry);
							break;
						case plane:
							//Should exist ???
							break;
						default:
							break;
					}
				break;

				default:
					break;
			}
			
		}
	iterationsUsed++;
	}

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

}
