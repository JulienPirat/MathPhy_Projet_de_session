#include "ParticleAnchoredSpring.h"

void ParticleAnchoredSpring::UpdateForce(Particle* particle, float duration)
{
	// Calculer le vecteur de la particule à l'ancrage
	Vector3D anchorToParticle = particle->getPosition() - m_anchor;

	// Calculer la longueur actuelle du ressort
	float longueurActuelle = anchorToParticle.magnitude();

	// Calculer la magnitude de la force en utilisant la loi de Hooke
	double magnitudeForce = -m_k * (longueurActuelle - m_restLength);

	// Calculer le vecteur de force
	anchorToParticle.operator*=(magnitudeForce);

	Vector3D ForceRessorLoiHooke = anchorToParticle;

	particle->addForce(ForceRessorLoiHooke);
}
