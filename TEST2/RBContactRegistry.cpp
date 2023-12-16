#include "RBContactRegistry.h"

void RBContactRegistry::ClearContactRegistry()
{
	contacts.clear();
}

bool RBContactRegistry::RemoveContact(RBContact* rbc)
{
	bool succesfullRemove = false;

	//std::vector<RBContact>::iterator elementsid = std::remove_if(contacts.begin(), contacts.end(), [](const RBContact& rb1, const RBContact& rb2) { return std::addressof(rb1) == std::addressof(rb2); });
	
	/*for (std::vector<RBContact>::iterator p = contacts.begin();
		p != elementsid; ++p) {
		contacts.erase(p);
		succesfullRemove = true;
	}*/

	std::vector<RBContact>::iterator i = contacts.begin();
	
	for (auto contact : contacts) {
		if (contact.RigidBodies[0] == rbc->RigidBodies[0] && contact.RigidBodies[1] == rbc->RigidBodies[1]) {
			contacts.erase(i);
			succesfullRemove = true;
		}
		i++;
	}
	
	return succesfullRemove;
}