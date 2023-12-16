#include "RBContactResolver.h"
#include <RBContactGenerator.h>

void RBContactResolver::resolveContacts(RBContactRegistry* ContactRegistry, unsigned int numContact, float duration, std::vector<std::pair<RigidBody*, RigidBody*>> potentialCollision)
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
			//ContactRegistry->contacts.erase(ContactRegistry->contacts.begin()+indexContactToResolve);

			

			ContactRegistry->RemoveContact(ContactRegistry->contacts[indexContactToResolve]);

			for (auto potCol : potentialCollision) {
				//On check quel genre de collision on va avoir besoin de rajouter
				if (potCol.first && potCol.second) {

					shapeRB SRB1 = potCol.first->shape; //Shape Rigidbody 1
					shapeRB SRB2 = potCol.second->shape; //Shape Rigidbody 2

					switch (SRB1)
					{
					case cuboide:
						//SRB1 CUBE
						switch (SRB2) {
						case cuboide:
							RBContactGenerator::boxAndBox((PBox*)potCol.first->primitive, (PBox*)potCol.second->primitive, ContactRegistry);
							break;
						case sphere:
							RBContactGenerator::boxAndSphere((PBox*)potCol.first->primitive, (PSphere*)potCol.second->primitive, ContactRegistry);
							break;
						case plane:
							RBContactGenerator::boxAndPlane((PBox*)potCol.first->primitive, (PPlane*)potCol.second->primitive, ContactRegistry);
							break;
						default:
							break;
						}
						break;
					case sphere:
						//SRB1 SPHERE
						switch (SRB2) {
						case cuboide:
							RBContactGenerator::boxAndSphere((PBox*)potCol.second->primitive, (PSphere*)potCol.first->primitive, ContactRegistry);
							break;
						case sphere:
							RBContactGenerator::sphereAndSphere((PSphere*)potCol.first->primitive, (PSphere*)potCol.second->primitive, ContactRegistry);
							break;
						case plane:
							RBContactGenerator::sphereAndPlane((PSphere*)potCol.first->primitive, (PPlane*)potCol.second->primitive, ContactRegistry);
							break;
						default:
							break;
						}
						break;
					case plane:
						//SRB1 PLANE
						switch (SRB2) {
						case cuboide:
							RBContactGenerator::boxAndPlane((PBox*)potCol.second->primitive, (PPlane*)potCol.first->primitive, ContactRegistry);
							break;
						case sphere:
							RBContactGenerator::sphereAndPlane((PSphere*)potCol.second->primitive, (PPlane*)potCol.first->primitive, ContactRegistry);
							break;
						case plane:
							//Should exist ???
							break;
						default:
							break;
						}
						break;
						break;
					default:
						break;
					}
				}
			}
			resolveContacts(ContactRegistry, numContact, duration, potentialCollision);

		}
			/*
			for (auto c : ContactRegistry->contacts)
			{
				Vector3D cp = Vector3D(0, 0, 0);
				if (c.RigidBodies[0] == ContactRegistry->contacts[indexContactToResolve].RigidBodies[0]) {

					cp = c.RigidBodies[0]->rotation.produitVectoriel(c.contactPoint);
					cp += c.RigidBodies[0]->velocity; // PAs sur car pas encore faire l'impulsion
					c.penetration -= cp.produitScalaire(c.contactNormal);
					ContactRegistry->contacts.erase(ContactRegistry->contacts.begin() + indexContactToResolve);
				}
				else if (c.RigidBodies[0] == ContactRegistry->contacts[indexContactToResolve].RigidBodies[1]) {
					cp = c.RigidBodies[1]->rotation.produitVectoriel(c.contactPoint);
					cp += c.RigidBodies[1]->velocity; // PAs sur car pas encore faire l'impulsion
					c.penetration -= cp.produitScalaire(c.contactNormal);
					ContactRegistry->contacts.erase(ContactRegistry->contacts.begin() + indexContactToResolve);
				}
				else if(c.RigidBodies[1] == ContactRegistry->contacts[indexContactToResolve].RigidBodies[0])
				{
					cp = c.RigidBodies[0]->rotation.produitVectoriel(c.contactPoint);
					cp += c.RigidBodies[0]->velocity; // PAs sur car pas encore faire l'impulsion
					c.penetration += cp.produitScalaire(c.contactNormal);
					ContactRegistry->contacts.erase(ContactRegistry->contacts.begin() + indexContactToResolve);
				}
				else if (c.RigidBodies[1] == ContactRegistry->contacts[indexContactToResolve].RigidBodies[1]) {
					cp = c.RigidBodies[1]->rotation.produitVectoriel(c.contactPoint);
					cp += c.RigidBodies[1]->velocity; // PAs sur car pas encore faire l'impulsion
					c.penetration += cp.produitScalaire(c.contactNormal);
					ContactRegistry->contacts.erase(ContactRegistry->contacts.begin() + indexContactToResolve);
				}
			}
			*/
			//ContactRegistry->RemoveContact(contactToResolveInterpenatration);
			

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
