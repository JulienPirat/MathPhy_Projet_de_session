#include "RBContact.h"

void RBContact::resolveInterpenetration(float duration)
{
	///////////////////////////////////	LIVRE	/////////////////////////////////////
	// Prepare the contacts for processing
	//prepareContacts(contacts, numContacts, duration);
	 
	// Resolve the interpenetration problems with the contacts.
	//adjustPositions(contacts, numContacts, duration);
	 
	// Resolve the velocity problems with the contacts.
	//adjustVelocities(contacts, numContacts, duration);
	///////////////////////////////////////////////////////////////////////////////////

	//	TODO :	Resolve the interpenetration problems with the contacts.
	
	auto LinearMoveRB0 = penetration * RigidBodies[0]->inverseMasse * (1 / (RigidBodies[0]->inverseMasse + RigidBodies[1]->inverseMasse));
	auto LinearMoveRB1 = -penetration * RigidBodies[1]->inverseMasse * (1 / (RigidBodies[0]->inverseMasse + RigidBodies[1]->inverseMasse));
	RigidBodies[0]->position = RigidBodies[0]->position + contactNormal * LinearMoveRB0;
	RigidBodies[1]->position = RigidBodies[1]->position + contactNormal * LinearMoveRB1;
	RigidBodies[0]->velocity = Vector3D(0, 0, 0);
	RigidBodies[1]->velocity = Vector3D(0, 0, 0);
}

void RBContact::AddImpulse(float duration)
{
	// Impulsion de couple

	// Vitesse au point de contact
	// Addition de la vitesse linéaire et de la vitesse rotationnelle	u1 = v1 + w1 x r1
	// v = vitesse linéaire; w = vitesse angulaire; r = le vecteur entre le centre de masse et point de contact
	//auto VitessePointContact = RigidBodies[0]->velocity + RigidBodies[0]->rotation;

	auto relativeVelocity = RigidBodies[0]->velocity - RigidBodies[1]->velocity;

	Vector3D r1 = RigidBodies[0]->position - contactPoint;
	Vector3D r2 = RigidBodies[1]->position - contactPoint;

	float k = restitution + 1;
	k = contactNormal.produitScalaire(relativeVelocity * k);
	float denominateur = contactNormal.produitScalaire((contactNormal * (RigidBodies[0]->inverseMasse + RigidBodies[1]->inverseMasse)
		+ ((r1 * contactNormal) * RigidBodies[0]->inverseI) * r1
		+ ((r2 * contactNormal) * RigidBodies[1]->inverseI) * r2));
	k = k / denominateur;

	// Vélocité après impulsion
	RigidBodies[0]->velocity = RigidBodies[0]->velocity - contactNormal * k * RigidBodies[0]->inverseMasse - k * ((r1 * contactNormal) * RigidBodies[0]->inverseI) * r1;
	RigidBodies[1]->velocity = RigidBodies[1]->velocity + contactNormal * k * RigidBodies[1]->inverseMasse + k * ((r2 * contactNormal) * RigidBodies[1]->inverseI) * r2;
}

float RBContact::calculateClosingVelocity()
{
	Vector3D relativeVelocity = RigidBodies[0]->velocity - RigidBodies[1]->velocity;
	return relativeVelocity * contactNormal;
}