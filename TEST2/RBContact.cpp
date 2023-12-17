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
	// Addition de la vitesse lineaire et de la vitesse rotationnelle	u1 = v1 + w1 x r1
	// v = vitesse lineaire; w = vitesse angulaire; r = le vecteur entre le centre de masse et point de contact

	// Calcul de la distance entre le point de contact et le centre de masse pour chaque objet
	Vector3D r1 = contactPoint - RigidBodies[0]->position;
	Vector3D r2 = contactPoint - RigidBodies[1]->position;

	// Calcul de la vitesse au point de contact pour chaque objet
	auto velocityAtContactPointRb1 = RigidBodies[0]->velocity + RigidBodies[0]->rotation.produitVectoriel(r1);
	auto velocityAtContactPointRb2 = RigidBodies[1]->velocity + RigidBodies[1]->rotation.produitVectoriel(r2);

	// Calcul de la vitesse relative
	auto relativeVelocity = RigidBodies[0]->velocity - RigidBodies[1]->velocity
		+ RigidBodies[0]->rotation.produitVectoriel(r1)
		- RigidBodies[1]->rotation.produitVectoriel(r2);

	// Calcul de l'impulsion k
	double numerateur = contactNormal.produitScalaire(relativeVelocity * (restitution + 1));
	double denominateur = contactNormal.produitScalaire(
		(contactNormal * (RigidBodies[0]->inverseMasse + RigidBodies[1]->inverseMasse)
		+ ((r1.produitVectoriel(contactNormal)) * RigidBodies[0]->inverseI).produitVectoriel(r1)
		+ ((r2.produitVectoriel(contactNormal)) * RigidBodies[1]->inverseI).produitVectoriel(r2))
	);
	double k = numerateur / denominateur;

	// Velocite lineaire apres impulsion
	RigidBodies[0]->velocity = RigidBodies[0]->velocity
		- (contactNormal * k * RigidBodies[0]->inverseMasse);
	RigidBodies[1]->velocity = RigidBodies[1]->velocity
		+ (contactNormal * k * RigidBodies[1]->inverseMasse);

	// Velocite angulaire apres impulsion
	RigidBodies[0]->rotation = RigidBodies[0]->rotation - ((r1.produitVectoriel(contactNormal * k)) * RigidBodies[0]->inverseI);
	RigidBodies[1]->rotation = RigidBodies[1]->rotation + ((r2.produitVectoriel(contactNormal * k)) * RigidBodies[1]->inverseI);
}

double RBContact::calculateClosingVelocity()
{
	Vector3D relativeVelocity = RigidBodies[0]->velocity - RigidBodies[1]->velocity;
	return relativeVelocity * contactNormal;
}