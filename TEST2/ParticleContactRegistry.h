#pragma once
#include <vector>
#include <ParticleContactGenerator.h>

class ParticleContactRegistry
{
public :

	///Attributes

	//Holds the list of contact generators.
	std::vector<ParticleContactGenerator*> contactRegistry;

	///Methodes

	//Detection des contacts
	void DetectContact(std::vector<Particle*>& particles);

	//Suppression du registre des contacts pour la prochaine frame
	void ClearContactRegistry();

};

