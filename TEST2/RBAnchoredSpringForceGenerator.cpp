#include "RBAnchoredSpringForceGenerator.h"

void RBAnchoredSpringForceGenerator::UpdateForce(RigidBody* rigidBody)
{
	// Calculate the vector of the spring
	auto force = rigidBody->transformMatrix * m_bodyAnchor;
	force -= m_WorldAnchor;

	// Calculate the magnitude of the force
	float magnitude = force.magnitude();
	magnitude = fabs(magnitude - m_restLenght);
	magnitude *= m_k;

	// Calculate the final frce and apply it
	force.normalize();
	force *= -magnitude;

	if (!(force == (Vector3D(0, 0, 0)))) {
		if (m_bodyAnchor.operator==(Vector3D(0, 0, 0))) {
			// Si l'origine du ressort est égale a l'origine du rigidBody
			rigidBody->AddForce(force);
		}
		else {
			rigidBody->AddForceAtBodyPoint(force, m_bodyAnchor);
		}
	}
}
