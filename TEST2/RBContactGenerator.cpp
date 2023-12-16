#include "RBContactGenerator.h"

unsigned RBContactGenerator::sphereAndSphere(PSphere* one, PSphere* two, RBContactRegistry* contactRegistry)
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

    contactRegistry->contacts.push_back(newContact);
    return 1;
}

unsigned RBContactGenerator::sphereAndPlane(PSphere* sphere, PPlane* plane, RBContactRegistry* contactRegistry)
{
    float distance = plane->normal * sphere->RB->position - plane->offset;
    
    if (distance > 0) 
    {
        // We don't have collision
        return 0;
    }

    Vector3D normalContact = plane->normal;
    float interpenatration = -distance; // car la distance est n�gative
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

    contactRegistry->contacts.push_back(newContact);

    return 1;
}

unsigned RBContactGenerator::boxAndPlane(PBox* box, PPlane* plane, RBContactRegistry* contactRegistry)
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
        contactRegistry->contacts.push_back(newContact);
    }


    return 1;
}

unsigned RBContactGenerator::boxAndSphere(PBox* box, PSphere* sphere, RBContactRegistry* contactRegistry)
{
    auto SpherePositionInBoxSpace = box->offset * sphere->RB->position;
    auto distanceX = SpherePositionInBoxSpace.x;
    if (distanceX > box->halfSize.x)
    {
		distanceX = box->halfSize.x;
	}
    if (distanceX < -box->halfSize.x)
    {
        distanceX = -box->halfSize.x;
    }

    auto distanceY = SpherePositionInBoxSpace.y;
    if (distanceY > box->halfSize.y)
    {
		distanceY = box->halfSize.y;
	}
    if (distanceY < -box->halfSize.y)
    {
		distanceY = -box->halfSize.y;
	}

    auto distanceZ = SpherePositionInBoxSpace.z;
    if (distanceZ > box->halfSize.z)
    {
        distanceZ = box->halfSize.z;
    }
    if (distanceZ < -box->halfSize.z)
    {
		distanceZ = -box->halfSize.z;
	}

    auto contactPoint = Vector3D(distanceX, distanceY, distanceZ);

    auto penetration = sphere->radius - (contactPoint - SpherePositionInBoxSpace).norme(); // Pas sur

    if (penetration <= 0) 
    {
        // We don't have collision
        return 0;
    }

    float restitution = (box->RB->linearDamping + sphere->RB->linearDamping) / 2;
    float friction = (box->RB->m_angularDamping + sphere->RB->m_angularDamping) / 2;

    auto normalContact = SpherePositionInBoxSpace - contactPoint;
    normalContact.normalize();
    

    RBContact newContact;
    newContact.contactNormal = normalContact;
    newContact.contactPoint = contactPoint;
    newContact.penetration = penetration;
    newContact.restitution = restitution;
    newContact.friction = friction;
    newContact.RigidBodies[0] = box->RB;
    newContact.RigidBodies[1] = sphere->RB;
    contactRegistry->contacts.push_back(newContact);

    return 1;
}

unsigned RBContactGenerator::boxAndBox(PBox* one, PBox* two, RBContactRegistry* contactRegistry)
{
    std::vector<Vector3D> Axes;

    Vector3D bOneX = (one->offset * Vector3D(1, 0, 0));   // boite 1 : X 
    Vector3D bOneY = (one->offset * Vector3D(0, 1, 0));   // boite 1 : Y
    Vector3D bOneZ = (one->offset * Vector3D(0, 0, 1));   // boite 1 : Z

    Vector3D bTwoX = (two->offset * Vector3D(1, 0, 0));   // boite 2 : X
    Vector3D bTwoY = (two->offset * Vector3D(0, 1, 0));   // boite 2 : Y
    Vector3D bTwoZ = (two->offset * Vector3D(0, 0, 1));   // boite 2 : Z

    // On r�cup�re les axes principaux des boites
    Axes.push_back(bOneX);
    Axes.push_back(bOneY);
    Axes.push_back(bOneZ);

    Axes.push_back(bTwoX);
    Axes.push_back(bTwoY);
    Axes.push_back(bTwoZ);

    // On r�cup�re les 9 autres axes

    Vector3D axeXX = bOneX.produitVectoriel(bTwoX);
    Vector3D axeXY = bOneX.produitVectoriel(bTwoY);
    Vector3D axeXZ = bOneX.produitVectoriel(bTwoZ);

    Vector3D axeYX = bOneY.produitVectoriel(bTwoX);
    Vector3D axeYY = bOneY.produitVectoriel(bTwoY);
    Vector3D axeYZ = bOneY.produitVectoriel(bTwoZ);

    Vector3D axeZX = bOneZ.produitVectoriel(bTwoX);
    Vector3D axeZY = bOneZ.produitVectoriel(bTwoY);
    Vector3D axeZZ = bOneZ.produitVectoriel(bTwoZ);

    Axes.push_back(axeXX);
    Axes.push_back(axeXY);
    Axes.push_back(axeXZ);

    Axes.push_back(axeYX);
    Axes.push_back(axeYY);
    Axes.push_back(axeYZ);

    Axes.push_back(axeZX);
    Axes.push_back(axeZY);
    Axes.push_back(axeZZ);

    for (Vector3D axe : Axes)
    {
		Interval intervalOne = ProjectBoxOnAxis(one, &axe);
        Interval intervalTwo = ProjectBoxOnAxis(two, &axe);

        if (intervalOne.min > intervalTwo.max || intervalTwo.min > intervalOne.max)
        {
			// We don't have collision
			return 0;
		}

        float restitution = (one->RB->linearDamping + two->RB->linearDamping) / 2;
        float friction = (one->RB->m_angularDamping + two->RB->m_angularDamping) / 2;
        

        if (axe == bOneX || axe == bOneY || axe == bOneZ ||
            axe == bTwoX || axe == bTwoY || axe == bTwoZ)
        {
            // Collision Face-Point
            float penetration = std::min(intervalOne.max - intervalTwo.min, intervalTwo.max - intervalOne.min); // Pas sur
            Vector3D contactPoint = intervalOne.Vertice + (intervalTwo.Vertice - intervalOne.Vertice) / 2; // Ne marche pas
            axe.normalize();
            
            RBContact newContact;
            newContact.contactNormal = axe;
            newContact.contactPoint = contactPoint;
            newContact.penetration = penetration;
            newContact.restitution = restitution;
            newContact.friction = friction;
            newContact.RigidBodies[0] = one->RB;
            newContact.RigidBodies[1] = two->RB;
            if(!penetration <= 0)
                contactRegistry->contacts.push_back(newContact);
        }
        else 
        {
            // Collision Edge-Edge

            float penetration = std::min(intervalOne.max - intervalTwo.min, intervalTwo.max - intervalOne.min); // Pas sur
            Vector3D contactPoint = intervalOne.Vertice + (intervalTwo.Vertice - intervalOne.Vertice) / 2; // Ne marche pas
            axe.normalize();

            RBContact newContact;
            newContact.contactNormal = axe;
            newContact.contactPoint = contactPoint;
            newContact.penetration = penetration;
            newContact.restitution = restitution;
            newContact.friction = friction;
            newContact.RigidBodies[0] = one->RB;
            newContact.RigidBodies[1] = two->RB;
            if (!penetration <= 0)
                contactRegistry->contacts.push_back(newContact);
        }
	}


    // Si fait partie des 6 axe principaux c'est un Point-Face sinon c'est un Edge-Edge
    // 6 Axes Principaux = X,Y,Z de chaque boite et les 9 autres axes = X*y, X*z,X*X ; Y*Y, Y*X,Y*Z ; ect...
    // En enlevant les doublons on obtient 15 axes

    // Ensuite on fait la projection des boites sur chaque axes et on calcule l'interp�netration.
    // On garde seulement les axes qui ont une interp�netration la plus petite possible.
    return 1;
}

Interval RBContactGenerator::ProjectBoxOnAxis(PBox* box, Vector3D* axis)
{
    std::vector<Vector3D> vertices = box->GetVertices();
    double dotProduct = axis->produitScalaire(vertices[0]);

    Interval interval;
    interval.min = dotProduct;
    interval.max = dotProduct;
    interval.Vertice = vertices[0];

    for (int i = 1; i < vertices.size(); i++)
    {
		dotProduct = axis->produitScalaire(vertices[i]);
        if (dotProduct < interval.min)
        {
            interval.Vertice = vertices[i];
        }
        interval.min = std::min(interval.min, dotProduct);
        interval.max = std::max(interval.max, dotProduct);
	}

    return interval;
}
