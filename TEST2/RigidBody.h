#pragma once
#include <Quaternion.h>
#include <Matrix4.h>
#include <Matrix3.h>
#include <PBox.h>
#include <PPlane.h>
#include <PSphere.h>

enum shapeRB {
	none = 0,
	cuboide = 1,
	sphere = 2,
	plane = 3
};

class RigidBody
{
public:

	///Attributes
	Primitive* primitive;

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

	//Inertie Matrix
	Matrix3 inverseI;

	//RigiBody Color
	Vector3D color;

	//Shape
	shapeRB shape = none;
	Vector3D dimension = Vector3D(1, 1, 1);

	///Constructeurs

	RigidBody();
	RigidBody(Matrix3 inverseInertia);
	RigidBody(Vector3D pos, Vector3D vel, Vector3D rotat, float linDamp, float angDamp, float mass, Vector3D col, Matrix3 inverseInertia);
	RigidBody(Vector3D pos, Vector3D vel, Vector3D rotat, float linDamp, float angDamp, float mass, Vector3D col, Matrix3 inverseInertia, shapeRB shape, Vector3D dimensions);

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
	void ClearAccumulators();

	friend bool operator==(const RigidBody& l, const RigidBody& r) {
		return l.position == r.position && l.velocity == r.velocity && l.orientation == r.orientation && l.rotation == r.rotation;
	}

private:

	//Call each frame to calculate the TransformMatrix and normalize the orientation
	void CalculateDerivedData();

	//Calculate the transform Matrix
	void CalculateTransformMatrix();

};

