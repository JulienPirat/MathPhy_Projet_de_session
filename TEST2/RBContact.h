#pragma once
#include <Vector3D.h>
#include <RigidBody.h>

class RBContact {

public:

	//Value between 0 - 1
	//Defining the elasticness of the collision
	float restitution;

	//Distance of penetration of the contact
	float penetration;

	//Normal of the contact
	Vector3D contactNormal;

	//Array of two RB
	RigidBody* RigidBodies[2];

	//Contact point in World Space
	Vector3D contactPoint;

	//Friction of the contact
	float friction;

	void resolveInterpenetration(float duration);

	void AddImpulse(float duration);

	//Return the closing velocity
	float calculateClosingVelocity();

	friend bool operator==(const RBContact& l, const RBContact& r) {
		return (l.RigidBodies[0] == r.RigidBodies[0] && l.RigidBodies[1] == r.RigidBodies[1]) 
			|| (l.RigidBodies[1] == r.RigidBodies[0] && l.RigidBodies[0] == r.RigidBodies[1]);
	}
};