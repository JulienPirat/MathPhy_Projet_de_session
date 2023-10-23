#pragma once
#include <Particle.h>

class ParticleContact
{
public :

	///Attributes

	//The 2 particles in contact
	Particle* particle[2];

	//Value between 0 - 1
	//Defining the elasticness of the collision
	float restitution;

	//Distance of penetration of the contact
	float penetration;

	//Normal of the contact
	Vector3D contactNormal;

	///Methodes

	//Resolve the velocity and interpenetration
	void resolve(float duration);

	//Return the separation velocity of the particles
	float calculateSeparatingVelocity();

private:
	//Handle impulse for the collision
	void resolveVelocity(float deltaT);

	//Handle interpenetration for the collision
	void resolveInterpenetration();
};

