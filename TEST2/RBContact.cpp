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
	

	//Matrix3 inverseInertiaTensor = RigidBodies[0]->inverseI;
	Matrix3 inverseInertiaTensor = (RigidBodies[0]->transformMatrix.ToMatrix3()) * RigidBodies[0]->inverseI * (RigidBodies[0]->transformMatrix.ToMatrix3().Inverse());
	Vector3D r = contactPoint - RigidBodies[0]->position;
	Vector3D angularInertiaWorld = r.produitVectoriel(contactNormal);
	angularInertiaWorld = inverseInertiaTensor * (angularInertiaWorld);
	angularInertiaWorld = angularInertiaWorld.produitVectoriel(r);
	float angularInertia = angularInertiaWorld.produitScalaire(contactNormal);

	//Matrix3 inverseInertiaTensor1 = RigidBodies[1]->inverseI;
	Matrix3 inverseInertiaTensor1 = (RigidBodies[1]->transformMatrix.ToMatrix3()) * RigidBodies[1]->inverseI * (RigidBodies[1]->transformMatrix.ToMatrix3().Inverse());
	Vector3D r1 = contactPoint - RigidBodies[1]->position;
	Vector3D angularInertiaWorld1 = r1.produitVectoriel(contactNormal);
	angularInertiaWorld1 = inverseInertiaTensor1 * (angularInertiaWorld1);
	angularInertiaWorld1 = angularInertiaWorld1.produitVectoriel(r1);
	float angularInertia1 = angularInertiaWorld1.produitScalaire(contactNormal);

	//auto inverseInertia = (1 / (RigidBodies[0]->inverseMasse + RigidBodies[1]->inverseMasse));
	//auto inverseInertiaAng = ((RigidBodies[0]->inverseI.Inverse() + RigidBodies[1]->inverseI.Inverse()).Inverse()).Inverse();
	auto inverseInertia = (1 / (RigidBodies[0]->inverseMasse + RigidBodies[1]->inverseMasse));
	auto inverseInertiaAng = angularInertia + angularInertia1;
	auto inverseTotal = inverseInertia + inverseInertiaAng;

	auto LinearMoveRB0 = penetration * RigidBodies[0]->inverseMasse * inverseInertia;
	auto LinearMoveRB1 = -penetration * RigidBodies[1]->inverseMasse * inverseInertia;
	auto AngularMoveRB0 = penetration * angularInertia * inverseInertiaAng;
	auto AngularMoveRB1 = -penetration * angularInertia1 * inverseInertiaAng;

	RigidBodies[0]->position = RigidBodies[0]->position + contactNormal * LinearMoveRB0;
	RigidBodies[1]->position = RigidBodies[1]->position + contactNormal * LinearMoveRB1;
	//RigidBodies[0]->rotation = RigidBodies[0]->rotation + AngularMoveRB0 * contactNormal;
	//RigidBodies[1]->rotation = RigidBodies[1]->rotation + AngularMoveRB1 * contactNormal;

	Vector3D rotationPerMove = inverseInertiaTensor * angularInertiaWorld;
	Vector3D rotationPerMove1 = inverseInertiaTensor1 * angularInertiaWorld1;

	Vector3D rotation = rotationPerMove * AngularMoveRB0;
	Vector3D rotation1 = rotationPerMove1 * AngularMoveRB1;

	//std::cout << "Rotate amount : " << rotation << "\n";

	//if () {
		RigidBodies[0]->orientation.rotateByVector(rotation, 50);
		RigidBodies[1]->orientation.rotateByVector(rotation1, 50);
		RigidBodies[0]->rotation += rotation * 20;
		RigidBodies[1]->rotation += rotation1 * 20;
		//std::cout << "Quat 1 " << RigidBodies[0]->orientation.i << "/" << RigidBodies[0]->orientation.j << "/" << RigidBodies[0]->orientation.k << "/" << std::endl;
		//std::cout << "Quat 2 " << RigidBodies[1]->orientation.i << "/" << RigidBodies[1]->orientation.j << "/" << RigidBodies[1]->orientation.k << "/" << std::endl;
	//}
}

void RBContact::AddImpulse(float duration)
{
	// Impulsion de couple

	// Vitesse au point de contact
	// Addition de la vitesse lin�aire et de la vitesse rotationnelle	u1 = v1 + w1 x r1
	// v = vitesse lin�aire; w = vitesse angulaire; r = le vecteur entre le centre de masse et point de contact
	//auto VitessePointContact = RigidBodies[0]->velocity + RigidBodies[0]->rotation;

	auto relativeVelocity = RigidBodies[0]->velocity - RigidBodies[1]->velocity;

	Vector3D r1 = RigidBodies[0]->position - contactPoint;
	Vector3D r2 = RigidBodies[1]->position - contactPoint;

	double e = restitution + 1;
	double numerateur = contactNormal.produitScalaire(relativeVelocity * e);
	double denominateur = contactNormal.produitScalaire((contactNormal * (RigidBodies[0]->inverseMasse + RigidBodies[1]->inverseMasse)
		+ ((r1 * contactNormal) * RigidBodies[0]->inverseI) * r1
		+ ((r2 * contactNormal) * RigidBodies[1]->inverseI) * r2));
	double k = numerateur / denominateur;

	// V�locit� apr�s impulsion
	RigidBodies[0]->velocity = RigidBodies[0]->velocity - contactNormal * k * RigidBodies[0]->inverseMasse - k * ((r1 * contactNormal) * RigidBodies[0]->inverseI) * r1;
	RigidBodies[1]->velocity = RigidBodies[1]->velocity + contactNormal * k * RigidBodies[1]->inverseMasse + k * ((r2 * contactNormal) * RigidBodies[1]->inverseI) * r2;

	Vector3D inverseInertiaTensor;
	//inverseInertiaTensor * 
	/*
	Vector3D impulsiveTorque = relativeContactPosition % contactNormal;
	Vector3D impulsePerMove = inverseInertiaTensor.produitVectoriel(impulsiveTorque);

	Vector3D rotationPerMove = impulsePerMove * (1/ RigidBodies[1]->inverseI.Inverse())

	RigidBodies[0]->orientation.rotateByVector(RigidBodies[0]->rotation, 1);
	RigidBodies[1]->orientation.rotateByVector(RigidBodies[1]->rotation, 1);*/
}

double RBContact::calculateClosingVelocity()
{
	Vector3D relativeVelocity = RigidBodies[0]->velocity - RigidBodies[1]->velocity;
	return relativeVelocity * contactNormal;
}