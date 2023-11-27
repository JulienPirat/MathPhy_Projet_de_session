#include "RBContactGenerator.h"

unsigned ContactGenerator::sphereAndSphere(PSphere* one, PSphere* two, RBContactRegistry* contactRegistry)
{

    float dx = one->RB->position.x - two->RB->position.x;
    float dy = one->RB->position.y - two->RB->position.y;
    float dz = one->RB->position.z - two->RB->position.z;
    float distance = sqrt(dx*dx + dy*dy + dz*dz);

    if(distance > one->radius + two->radius)
	{
		// We don't have collision
		return 0;
	}
	
    Vector3D normalContact = one->RB->position - two->RB->position;
    normalContact.norme();

    float interpenetration = one->radius + two->radius - distance;
    Vector3D contactPoint = one->RB->position + normalContact * one->radius; //Pas sur
    float restitution = (one->RB->linearDamping + two->RB->linearDamping) / 2;
    float friction = (one->RB->m_angularDamping + two->RB->m_angularDamping) / 2;

    RBContact newContact;
    newContact.contactNormal = normalContact;
    newContact.contactPoint = contactPoint;
    newContact.penetration = interpenetration;
    newContact.restitution = restitution;
	newContact.friction = friction;
    newContact.RigidBodies[0] = one->RB;
    newContact.RigidBodies[1] = two->RB;

    contactRegistry->contacts->push_back(newContact);
    return 1;
}
