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

	//Same as linear damping but for rotation
	float m_angularDamping;

	//Accumulate force added by Force Generator
	Vector3D m_forceAccum;

	//Accumulated torque added by Force Generator
	Vector3D m_torqueAccum;

public:

	///Methodes
	
	//Integrate the rigidbody by modifying position, orientation and velocity;
	void Integrate(float duration);

	//Add Force on the center of mass (no torque generated)
	void AddForce(const Vector3D& force);

	//Add force at a point in world coordinate. Generated force and torque
	void AddForceAtPoint(const Vector3D& force, const Vector3D& worldPoint);

	//Add force at a point in local coordinate. The point is converted in world coordinated by using the transform matrix. Generate force and torque.
	void AddForceAtBodyPoint(const Vector3D& force, const Vector3D& localPoint);

	//Called each frame to reset 
	void ClearAccumulator();

private:

	//Call each frame to calculate the TransformMatrix and normalize the orientation
	void CalculateDerivedData();

	//Calculate the transform Matrix
	void CalculateTransformMatrix();
};

