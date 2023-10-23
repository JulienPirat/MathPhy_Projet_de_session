#include "ParticleSpring.h"

void ParticleSpring::UpdateForce(Particle* particle, float duration)
{
	//Calculate the vector of the spring
	Vector3D force = particle->getPosition();
	force -= m_other->getPosition();

	//Calculate the magnitude of the force
	float magnitude = force.magnitude();
	magnitude = fabs(magnitude - m_restLength);
	magnitude *= springConstant;

	//Calculate the final force and apply it
	force.normalize();
	force *= -magnitude;
	particle->addForce(force);
}
