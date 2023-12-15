#include "RBContactRegistry.h"

void RBContactRegistry::ClearContactRegistry()
{
	contacts.clear();
}

bool RBContactRegistry::RemoveContact(RBContact* rb)
{
	std::remove_if(contacts.begin(), contacts.end(), [](const RBContact& rb1, const RBContact& rb2) { return std::addressof(rb1) == std::addressof(rb2); });
}