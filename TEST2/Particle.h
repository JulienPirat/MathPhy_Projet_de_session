#pragma once
#include "Vector3D.h"
/**
* L'objet le plus simple pouvant �tre simul� dans un jeu.
*/
class Particle
{
public:

	//Constructeur de la classe
	Particle();
	Particle(Vector3D pos, Vector3D vel, Vector3D acc, double damp, double mass);

	//Contient la position de la particule dans le monde
	Vector3D position;
	//Contient la vitesse de la particule dans le monde
	Vector3D velocity;
	/**
	* Contient l'acc�l�ration de la particule dans le monde
	* Cette valeur peut servir � appliquer une force constante sur la particule tel que la gravit�
	*/
	Vector3D acceleration;

	//R�sistance au d�placement. Retire de l'energie � notre d�placement
	double damping;

	//Masse inverse de notre particule
	double inverseMass;

	//Contients la somme des force qui sera appliqu� a la prochaine frame
	Vector3D forceAccum;

	//M�thode pour remettre � 0 le cumul des forces de chaque frame
	void clearAccumulator();

	//Ajout d'une force � la particule
	void addForce(const Vector3D& force);

	//Mise � jour de la particule � travers le temps
	void Integrate(double duration);

	//void PositionUpdate(double* time);
};


