#pragma once
#include <Quaternion.h>
#include <Matrix4.h>

class RigidBody
{
private :

	///Attributes

	//Identical as Particle
	float inverseMasse;
	float linearDamping;
	Vector3D position;
	Vector3D velocity;

	//RigidBody Orientation
	Quaternion orientation;

	//Angular Velocity of the RigidBody
	Vector3D rotation;

	//Calculates transform matrix from orientation and rotation
	Matrix4 transformMatrix;

public:

	///Methodes
	
	//Integrate the rigidbody by modifying position, orientation and velocity;
	void Integrate(float duration);

private:

	//Call each frame to calculate the TransformMatrix and normalize the orientation
	void CalculateDerivedData();
};

