#include "Particle.h"
#include <cmath>

Particle::Particle() {
	position = Vector3D();
	velocity = Vector3D();
	acceleration = Vector3D();
	damping = 0.9f;
	inverseMass = 1;
	clearAccumulator();
}

Particle::Particle(Vector3D pos, Vector3D vel, Vector3D acc, double damp, double mass) {
	position = pos;
	velocity = vel;
	acceleration = acc;
	damping = damp;
	inverseMass = 1 / mass;
	clearAccumulator();
}

/*
void Particle::PositionUpdate(double* time) {
	position.addScaledVector(velocity, *time);
	position.addScaledVector(acceleration, *time * *time * 0.5);
}
*/

void Particle::clearAccumulator()
{
	forceAccum = Vector3D();
}

void Particle::addForce(const Vector3D& force)
{
	forceAccum = forceAccum + force;
}

void Particle::Integrate(double duration)
{
	if (duration < 0.0) {
		std::cout << "ERREUR DURATION SHOULDN'T BE 0 OR LESS !" << std::endl;
		return;
	}

	// Met � jour la position
	position.addScaledVector(velocity, duration);

	// Calcul de l'acc�l�ration � partir des forces
	Vector3D resultingAcc = acceleration;
	resultingAcc.addScaledVector(forceAccum, inverseMass);

	// Mise � jour de la vitesse � partir de l'acceleration
	velocity.addScaledVector(resultingAcc, duration);

	// R�sistance Impos�e
	velocity = velocity * pow(damping, duration);

	//Remise � 0 des forces pour la prochaine frame
	clearAccumulator();
}
