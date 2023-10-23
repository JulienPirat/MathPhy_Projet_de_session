#include "ParticleDrag.h"

void ParticleDrag::UpdateForce(Particle* particle, float duration)
{
	//Calculate the total drag coefficient
	float dragCoeff = particle->getVelocity().magnitude();
	dragCoeff = m_k1 * dragCoeff + m_k2 * dragCoeff * dragCoeff;

	//Calculate the final force and apply it
	Vector3D force = particle->getVelocity();
	force.normalize();
	force *= -dragCoeff;
	particle->addForce(force);
}
