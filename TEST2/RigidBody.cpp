#include "RigidBody.h"

void RigidBody::Integrate(float duration)
{

	// Check if duration is valid
	if (duration < 0.0) {
		std::cout << "ERREUR DURATION SHOULDN'T BE 0 OR LESS !" << std::endl;
		return;
	}

	// Position Update
	position.addScaledVector(velocity, duration);

	//Orientation Update
	orientation.UpdateByAngularVelocity(rotation, duration);

	// Calculate Acceleration based on forces
	Vector3D resultingAcc = Vector3D(0,0,0);
	resultingAcc.addScaledVector(m_forceAccum, inverseMasse);

	// Caculate Angular acceleration based on forces
	Vector3D resultingAngAcc = Vector3D(0, 0, 0);
	resultingAcc.addScaledVector(m_torqueAccum, inverseMasse);


	// Update Velocity based on Acceleration
	velocity.addScaledVector(resultingAngAcc, duration);

	//Update Angular Velocity based on Angular Acceleration
	rotation.addScaledVector(resultingAcc, duration);


	// Damping 
	velocity = velocity * powf(linearDamping, duration);

	// Angular Damping
	rotation = rotation * powf(m_angularDamping, duration);


	//In last recalculate the transform matrix after the integration
	CalculateDerivedData();

	//Reset All Accumulators
	ClearAccumulators();

}

void RigidBody::AddForce(const Vector3D& force)
{
	m_forceAccum += force;
}

void RigidBody::AddForceAtPoint(const Vector3D& force, const Vector3D& worldPoint)
{
	//find distance between worldpoint and position
	auto distance = worldPoint - position;
	//find angle between distance and force
	auto angle = acos(distance.produitScalaire(force) / (distance.magnitude() * force.magnitude()));
	//calculate torque
	auto torque = force * sin(angle) * distance.magnitude();
	//add torque to torque accumulator
	m_torqueAccum += torque;
	//add force to force accumulator
	m_forceAccum += force;
}

void RigidBody::AddForceAtBodyPoint(const Vector3D& force, const Vector3D& localPoint)
{
	auto WorldPoint = transformMatrix * localPoint;
	AddForceAtPoint(force, WorldPoint);
}

void RigidBody::ClearAccumulators()
{
	m_forceAccum = Vector3D(0, 0, 0);
	m_torqueAccum = Vector3D(0, 0, 0);
}

void RigidBody::CalculateDerivedData()
{
	//Calculate the transform matrix for the body
	CalculateTransformMatrix();
	
}

void RigidBody::CalculateTransformMatrix()
{
	//Reflection matrix as seen here : https://en.wikipedia.org/wiki/Transformation_matrix#Reflection_2
	transformMatrix.data[0] = 1 - 2 * orientation.j * orientation.j - 2 * orientation.k * orientation.k;
	transformMatrix.data[1] = 2 * orientation.i * orientation.j * orientation.k - 2 * orientation.r * orientation.k;
	transformMatrix.data[2] = 2 * orientation.i * orientation.k + 2 * orientation.r * orientation.j;
	transformMatrix.data[3] = position.x;

	transformMatrix.data[4] = 2 * orientation.i * orientation.j * orientation.k + 2 * orientation.r * orientation.k;
	transformMatrix.data[5] = 1 - 2 * orientation.i * orientation.i - 2 * orientation.k * orientation.k;
	transformMatrix.data[6] = 2 * orientation.j * orientation.k - 2 * orientation.r * orientation.i;
	transformMatrix.data[7] = position.y;

	transformMatrix.data[8] = 2 * orientation.i * orientation.k - 2 * orientation.r * orientation.j;
	transformMatrix.data[9] = 2 * orientation.j * orientation.k + 2 * orientation.r * orientation.i;
	transformMatrix.data[10] = 1 - 2 * orientation.i * orientation.i - 2 * orientation.j * orientation.j;
	transformMatrix.data[11] = position.z;
}