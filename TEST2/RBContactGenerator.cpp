#include "RBContactGenerator.h"
#include <PPlane.h>

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

unsigned ContactGenerator::sphereAndPlane(PSphere* sphere, PPlane* plane, RBContactRegistry* contactRegistry)
{
    float distance = plane->normal * sphere->RB->position - plane->offset;
    
    if (distance > 0) 
    {
        // We don't have collision
        return 0;
    }

    Vector3D normalContact = plane->normal;
    float interpenatration = -distance; // car la distance est négative
    Vector3D contactPoint = sphere->RB->position - plane->normal * (distance + sphere->radius);
	float restitution = (sphere->RB->linearDamping + plane->RB->linearDamping) / 2;
    float friction = (sphere->RB->m_angularDamping + plane->RB->m_angularDamping) / 2;

    RBContact newContact;
    newContact.contactNormal = normalContact;
    newContact.contactPoint = contactPoint;
    newContact.penetration = interpenatration;
    newContact.restitution = restitution;
    newContact.friction = friction;
    newContact.RigidBodies[0] = sphere->RB;
    newContact.RigidBodies[1] = plane->RB;

    contactRegistry->contacts->push_back(newContact);

    return 1;
}

unsigned ContactGenerator::boxAndPlane(PBox* box, PPlane* plane, RBContactRegistry* contactRegistry)
{
    auto vertices = box->GetVertices();

    for (auto& vertice : vertices)
    {
        auto distance = vertice * plane->normal - plane->offset;
        if (distance > 0)
        {
			// We don't have collision
			return 0;
		}

        float restitution = (box->RB->linearDamping + plane->RB->linearDamping) / 2;
        float friction = (box->RB->m_angularDamping + plane->RB->m_angularDamping) / 2;

        auto contactPoint = vertice - plane->normal * (distance + box->halfSize.x); //Pas sur

        RBContact newContact;
        newContact.contactNormal = plane->normal;
        newContact.contactPoint = contactPoint;
        newContact.penetration = distance;
        newContact.restitution = restitution;
        newContact.friction = friction;
        newContact.RigidBodies[0] = box->RB;
        newContact.RigidBodies[1] = plane->RB;
        contactRegistry->contacts->push_back(newContact);
    }


    return 1;
}
