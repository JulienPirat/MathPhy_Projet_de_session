#pragma once
#include <Vector3D.h>
#include <RigidBody.h>

class RBContact {

public:

	//Value between 0 - 1
	//Defining the elasticness of the collision
	double restitution;

	//Distance of penetration of the contact
	double penetration;

	//Normal of the contact
	Vector3D contactNormal;

	//Array of two RB
	RigidBody* RigidBodies[2];

	//Contact point in World Space
	Vector3D contactPoint;

	//Friction of the contact
	double friction;

	void resolveInterpenetration(float duration);

	void AddImpulse(float duration);

	//Return the closing velocity
	double calculateClosingVelocity();

	friend bool operator==(const RBContact& l, const RBContact& r) {
		return ((l.RigidBodies[0] == r.RigidBodies[0] && l.RigidBodies[1] == r.RigidBodies[1])
			|| (l.RigidBodies[1] == r.RigidBodies[0] && l.RigidBodies[0] == r.RigidBodies[1]))
			&& l.contactNormal == r.contactNormal
			&& l.contactPoint == r.contactPoint
			&& l.penetration == r.penetration
			&& l.restitution == r.restitution 
			&& l.friction == r.friction;
	}
};