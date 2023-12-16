#include "RBContactRegistry.h"

void RBContactRegistry::ClearContactRegistry()
{
	contacts.clear();
}

void RBContactRegistry::RemoveContact(RBContact rbc)
{
	auto it = std::remove_if(contacts.begin(), contacts.end(), [&rbc](RBContact rbOther) { 
		return rbc == rbOther; 
	});
	if(it != contacts.end())
		contacts.erase(it, contacts.end());
}

void RBContactRegistry::RemoveAllContactsFromTwoRigidBodies(RigidBody* rb1, RigidBody* rb2)
{
	auto it = std::remove_if(contacts.begin(), contacts.end(), [&rb1, &rb2](RBContact rbOther) {
		return (rb1 == rbOther.RigidBodies[0] && rb2 == rbOther.RigidBodies[1]) || (rb2 == rbOther.RigidBodies[0] && rb1 == rbOther.RigidBodies[1]);
	});
	if (it != contacts.end())
		contacts.erase(it, contacts.end());
}