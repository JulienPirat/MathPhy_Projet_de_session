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
	k = relativeVelocity * k * contactNormal;
	//k = k / ((RigidBodies[0]->inverseMasse + RigidBodies[1]->inverseMasse) * contactNormal + ((r1 * contactNormal) * RigidBodies[0]->inverseI) * r1);
	//TODO : Corrigez ça avec le retour du prof
	

	// Vélocité après impulsion
	RigidBodies[0]->velocity = RigidBodies[0]->velocity - contactNormal * k * RigidBodies[0]->inverseMasse - k * ((r1 * contactNormal) * RigidBodies[0]->inverseI) * r1;
	RigidBodies[1]->velocity = RigidBodies[1]->velocity + contactNormal * k * RigidBodies[1]->inverseMasse + k * ((r2 * contactNormal) * RigidBodies[1]->inverseI) * r2;
}

float RBContact::calculateClosingVelocity()
{
	Vector3D relativeVelocity = RigidBodies[0]->velocity - RigidBodies[1]->velocity;
	return relativeVelocity * contactNormal;
}
