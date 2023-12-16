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
	double restitution;

	//Distance of penetration of the contact
	double penetration;

	//Normal of the contact
	Vector3D contactNormal;

	///Methodes

	//Resolve the velocity and interpenetration
	void resolve(double duration);

	//Return the separation velocity of the particles
	double calculateSeparatingVelocity();

private:
	//Handle impulse for the collision
	void resolveVelocity(double deltaT);

	//Handle interpenetration for the collision
	void resolveInterpenetration();
};

