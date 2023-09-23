#pragma once
#include "Vector3D.h"
/**
* L'objet le plus simple pouvant être simulé dans un jeu.
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
	* Contient l'accélération de la particule dans le monde
	* Cette valeur peut servir à appliquer une force constante sur la particule tel que la gravité
	*/
	Vector3D acceleration;

	//Résistance au déplacement. Retire de l'energie à notre déplacement
	double damping;

	//Masse inverse de notre particule
	double inverseMass;

	//Contients la somme des force qui sera appliqué a la prochaine frame
	Vector3D forceAccum;

	//Méthode pour remettre à 0 le cumul des forces de chaque frame
	void clearAccumulator();

	//Ajout d'une force à la particule
	void addForce(const Vector3D& force);

	//Mise à jour de la particule à travers le temps
	void Integrate(double duration);

	//void PositionUpdate(double* time);
};


