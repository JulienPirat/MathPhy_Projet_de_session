#include "RBContactRegistry.h"

void RBContactRegistry::ClearContactRegistry()
{
	contacts.clear();
}

void RBContactRegistry::RemoveContact(RBContact rbc)
{
	std::remove_if(contacts.begin(), contacts.end(), [&](RBContact rbOther) { return std::addressof(rbc) == std::addressof(rbOther); });
}