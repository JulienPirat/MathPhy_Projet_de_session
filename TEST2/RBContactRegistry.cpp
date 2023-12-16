#include "RBContactRegistry.h"

void RBContactRegistry::ClearContactRegistry()
{
	contacts.clear();
}

void RBContactRegistry::RemoveContact(RBContact rbc)
{
	auto it = std::remove_if(contacts.begin(), contacts.end(), [&rbc](RBContact rbOther) { return rbc == rbOther; });
	if(it != contacts.end())
		contacts.erase(it, contacts.end());
}