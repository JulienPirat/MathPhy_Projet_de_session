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

Particle::Particle(Vector3D pos, Vector3D vel, Vector3D acc, double damp, double mass, Color color) {
	position = pos;
	velocity = vel;
	acceleration = acc;
	damping = damp;
	inverseMass = 1 / mass;
	this->color = color;
	clearAccumulator();
}

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

	// Met à jour la position
	position.addScaledVector(velocity, duration);

	// Calcul de l'accélération à partir des forces
	Vector3D resultingAcc = acceleration;
	resultingAcc.addScaledVector(forceAccum, inverseMass);

	// Mise à jour de la vitesse à partir de l'acceleration
	velocity.addScaledVector(resultingAcc, duration);

	// Résistance Imposée
	velocity = velocity * pow(damping, duration);

	//Remise à 0 des forces pour la prochaine frame
	clearAccumulator();
}

#pragma region Getters/Setters
Vector3D Particle::getPosition() const
{
	return position;
}

Vector3D Particle::getVelocity() const
{
	return velocity;
}

Vector3D Particle::getAcceleration() const
{
	return acceleration;
}

double Particle::getDamping() const
{
	return damping;
}

double Particle::getInverseMass() const
{
	return inverseMass;
}

Color Particle::getColor() const
{
	return color;
}

void Particle::setPosition(Vector3D pos)
{
	position = pos;
}

void Particle::setVelocity(Vector3D vel)
{
	velocity = vel;
}

void Particle::setAcceleration(Vector3D acc)
{
	acceleration = acc;
}

void Particle::setDamping(double damp)
{
	damping = damp;
}

void Particle::setInverseMass(double mass)
{
	inverseMass = 1 / mass;
}

void Particle::setColor(Color col)
{
	color = col;
}
#pragma endregion