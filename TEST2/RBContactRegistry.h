#pragma once
#include <RBContact.h>
#include <vector>

class RBContactRegistry
{
public:
	std::vector<RBContact> contacts;

	//Suppression du registre des contacts pour la prochaine frame
	void ClearContactRegistry();

	void RemoveContact(RBContact rbc);
};