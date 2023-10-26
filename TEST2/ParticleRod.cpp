#include "ParticleRod.h"

float ParticleRod::currentLength() const
{
	Vector3D relativePos = particle[0]->getPosition() - particle[1]->getPosition();
	return relativePos.magnitude();
}

unsigned int ParticleRod::addContact(ParticleContactRegistry* ContactRegistry, unsigned int limit) const
{
	//Find the length of the rod
	float current = currentLength();
	//std::cout << "taille cable : " << current;
	//Check if the rod is overextended
	if (current == length)
	{
		return 0;
	}

	ParticleContact contact;

	//Otherwise return the contact
	contact.particle[0] = particle[0];
	contact.particle[1] = particle[1];

	//Calculate the normal
	Vector3D normal = particle[1]->getPosition() - particle[0]->getPosition();
	normal.normalize();

	//The contact normal depends on the length of the rod
	if (current > length)
	{
		contact.contactNormal = normal;
		contact.penetration = current - length;
	}
	else
	{
		contact.contactNormal = normal * -1;
		contact.penetration = length - current;
	}

	//Always use zero restitution
	contact.restitution = 0;
	ContactRegistry->Contacts.push_back(contact);

	return limit--;
}
