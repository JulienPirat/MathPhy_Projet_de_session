#pragma once
#include <vector>
#include <ParticleContactGenerator.h>

class ParticleContactRegistry
{
public :

	///Attributes

	//Holds the list of contact generators.
	std::vector<ParticleContact> Contacts;

	///Methodes

	//Suppression du registre des contacts pour la prochaine frame
	void ClearContactRegistry();

};

