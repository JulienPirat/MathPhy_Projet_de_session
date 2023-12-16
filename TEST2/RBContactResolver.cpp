#include "RBContactResolver.h"
#include <RBContactGenerator.h>

void RBContactResolver::resolveContacts(RBContactRegistry* ContactRegistry, unsigned int numContact, float duration)
{


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
		RBContact& contactToResolveInterpenatration = ContactRegistry->contacts[0];

		if (!ContactRegistry->contacts.empty())
		{
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
			//ContactRegistry->contacts.erase(ContactRegistry->contacts.begin()+indexContactToResolve);
		}

		std::vector<RBContact> ContactRestants = ContactRegistry->contacts;

		ContactRegistry->RemoveContact(ContactRegistry->contacts[indexContactToResolve]);

		//RigidBody* TempRB1 = ContactRestants[indexContactToResolve].RigidBodies[0];
		//RigidBody* TempRB2 = ContactRestants[indexContactToResolve].RigidBodies[1];

		for (auto potCol : ContactRestants) {
			//On check quel genre de collision on va avoir besoin de rajouter
			if (potCol.RigidBodies[0] && potCol.RigidBodies[1]) {

				shapeRB SRB1 = potCol.RigidBodies[0]->shape; //Shape Rigidbody 1
				shapeRB SRB2 = potCol.RigidBodies[1]->shape; //Shape Rigidbody 2

				switch (SRB1)
				{
				case cuboide:
					//SRB1 CUBE
					switch (SRB2) {
					case cuboide:
						RBContactGenerator::boxAndBox((PBox*)potCol.RigidBodies[0]->primitive, (PBox*)potCol.RigidBodies[1]->primitive, ContactRegistry);
						break;
					case sphere:
						RBContactGenerator::boxAndSphere((PBox*)potCol.RigidBodies[0]->primitive, (PSphere*)potCol.RigidBodies[1]->primitive, ContactRegistry);
						break;
					case plane:
						RBContactGenerator::boxAndPlane((PBox*)potCol.RigidBodies[0]->primitive, (PPlane*)potCol.RigidBodies[1]->primitive, ContactRegistry);
						break;
					default:
						break;
					}
					break;
				case sphere:
					//SRB1 SPHERE
					switch (SRB2) {
					case cuboide:
						RBContactGenerator::boxAndSphere((PBox*)potCol.RigidBodies[1]->primitive, (PSphere*)potCol.RigidBodies[0]->primitive, ContactRegistry);
						break;
					case sphere:
						RBContactGenerator::sphereAndSphere((PSphere*)potCol.RigidBodies[0]->primitive, (PSphere*)potCol.RigidBodies[1]->primitive, ContactRegistry);
						break;
					case plane:
						RBContactGenerator::sphereAndPlane((PSphere*)potCol.RigidBodies[0]->primitive, (PPlane*)potCol.RigidBodies[1]->primitive, ContactRegistry);
						break;
					default:
						break;
					}
					break;
				case plane:
					//SRB1 PLANE
					switch (SRB2) {
					case cuboide:
						RBContactGenerator::boxAndPlane((PBox*)potCol.RigidBodies[1]->primitive, (PPlane*)potCol.RigidBodies[0]->primitive, ContactRegistry);
						break;
					case sphere:
						RBContactGenerator::sphereAndPlane((PSphere*)potCol.RigidBodies[1]->primitive, (PPlane*)potCol.RigidBodies[0]->primitive, ContactRegistry);
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
		//resolveContacts(ContactRegistry, numContact, duration, potentialCollision);

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
