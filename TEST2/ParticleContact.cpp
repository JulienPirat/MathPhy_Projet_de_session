#include "ParticleContact.h"

void ParticleContact::resolve(float duration)
{
	resolveVelocity(duration);
	resolveInterpenetration();
}

float ParticleContact::calculateSeparatingVelocity()
{
	Vector3D relativeVelocity = particle[0]->getVelocity();
	if (particle[1]) relativeVelocity -= particle[1]->getVelocity();
	return relativeVelocity * contactNormal;
}

void ParticleContact::resolveVelocity(float deltaT)
{
	auto relativeVelocity = particle[0]->getVelocity() - particle[1]->getVelocity();

	float k = restitution + 1;
	k = relativeVelocity * k * contactNormal;
	k = k / (particle[0]->getInverseMass() + particle[1]->getInverseMass());

	//On multiplie au lieu de diviser car on travaille avec la masse inverse
	particle[0]->setVelocity(particle[0]->getVelocity() - contactNormal * k * particle[0]->getInverseMass());	
	particle[1]->setVelocity(particle[1]->getVelocity() + contactNormal * k * particle[1]->getInverseMass());
}

void ParticleContact::resolveInterpenetration()
{
	// If we don’t have any penetration, skip this step.
	if (penetration <= 0) {
		return;
	}

	// The movement of each object is based on its inverse mass, so
	// total that.
	float totalInverseMass = particle[0]->getInverseMass();
	if (particle[1]) {
		totalInverseMass += particle[1]->getInverseMass();
	}

	// If all particles have infinite mass, then we do nothing.
	if (totalInverseMass <= 0) return;

	// Find the amount of penetration resolution per unit of inverse mass.
	Vector3D movePerIMass = contactNormal * (-penetration / totalInverseMass);

	// Apply the penetration resolution.
	particle[0]->setPosition(particle[0]->getPosition() + movePerIMass * particle[0]->getInverseMass());
	if (particle[1])
	{
		particle[1]->setPosition(particle[1]->getPosition() +
			movePerIMass * particle[1]->getInverseMass());
	}
}
