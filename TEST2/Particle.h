#pragma once
#include "Vector3D.h"
#include <RigidBody.h>
/**
* L'objet le plus simple pouvant �tre simul� dans un jeu.
*/

class Particle
{
public:

	//Constructeur de la classe
	Particle();
	Particle(Vector3D pos, Vector3D vel, Vector3D acc, double damp, double mass, Color color);

	///Methodes

	//M�thode pour remettre � 0 le cumul des forces de chaque frame
	void clearAccumulator();

	//Ajout d'une force � la particule
	void addForce(const Vector3D& force);

	//Mise � jour de la particule � travers le temps
	void Integrate(double duration);

	//void PositionUpdate(double* time);

	//Getters
	Vector3D getPosition() const;
	Vector3D getVelocity() const;
	Vector3D getAcceleration() const;
	double getDamping() const;
	double getInverseMass() const;
	Color getColor() const;

	//Setters
	void setPosition(Vector3D pos);
	void setVelocity(Vector3D vel);
	void setAcceleration(Vector3D acc);
	void setDamping(double damp);
	void setInverseMass(double mass);
	void setColor(Color col);

	///Attributes

	bool isResting = false;
	
	private:
		//Position de la particule
		Vector3D position;

		//Vitesse de la particule
		Vector3D velocity;

		//Acc�l�ration de la particule
		Vector3D acceleration;

		//Damping de la particule
		double damping;

		//Inverse de la masse de la particule
		double inverseMass;

		//Force accumul�e par la particule
		Vector3D forceAccum;

		//Couleur de la particule
		Color color;
};


