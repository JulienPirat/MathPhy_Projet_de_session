#include "RBContactGenerator.h"

unsigned RBContactGenerator::sphereAndSphere(PSphere* one, PSphere* two, RBContactRegistry* contactRegistry)
{

    double dx = one->RB->position.x - two->RB->position.x;
    double dy = one->RB->position.y - two->RB->position.y;
    double dz = one->RB->position.z - two->RB->position.z;
    double distance = sqrt(dx*dx + dy*dy + dz*dz);

    if(distance > one->radius + two->radius)
	{
		// We don't have collision
		return 0;
	}
	
    Vector3D normalContact = one->RB->position - two->RB->position;
    normalContact.norme();

    double interpenetration = one->radius + two->radius - distance;
    if(interpenetration < 0.001)
        return 0;
    Vector3D contactPoint = one->RB->position + normalContact * one->radius; //Pas sur
    double restitution = (one->RB->linearDamping + two->RB->linearDamping) / 2;
    double friction = (one->RB->m_angularDamping + two->RB->m_angularDamping) / 2;

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
    double distance = plane->normal * sphere->RB->position - plane->offsetP - sphere->radius;
    
    if (distance > 0) 
    {
        // We don't have collision
        return 0;
    }

    Vector3D normalContact = plane->normal;
    double interpenatration = -distance; // car la distance est négative
    Vector3D contactPoint = sphere->RB->position - plane->normal * distance;
    double restitution = (sphere->RB->linearDamping + plane->RB->linearDamping) / 2;
    double friction = (sphere->RB->m_angularDamping + plane->RB->m_angularDamping) / 2;

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
        auto distance = vertice * plane->normal - plane->offsetP;
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
        newContact.penetration = abs(distance);
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
    auto SpherePositionInBoxSpace = sphere->RB->position - box->RB->position;
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

    auto penetration = (SpherePositionInBoxSpace - contactPoint).magnitude();
    /*
    if (penetration < 0 || penetration >= 1) 
    {
        // We don't have collision
        return 0;
    }*/

    if (penetration > sphere->radius * sphere->radius)
    {
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
    newContact.RigidBodies[1] = box->RB;
    newContact.RigidBodies[0] = sphere->RB;

    //if(penetration <= 0)
    //    return 0;
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

    // On récupère les axes principaux des boites
    Axes.push_back(bOneX);
    Axes.push_back(bOneY);
    Axes.push_back(bOneZ);

    Axes.push_back(bTwoX);
    Axes.push_back(bTwoY);
    Axes.push_back(bTwoZ);

    // On récupère les 9 autres axes

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
        //axe.normalize();
		Interval intervalOne = ProjectBoxOnAxis(one, &axe);
        Interval intervalTwo = ProjectBoxOnAxis(two, &axe);

        if (intervalOne.min > intervalTwo.max || intervalTwo.min > intervalOne.max)
        {
			// We don't have collision
			return 0;
		}

        double restitution = (one->RB->linearDamping + two->RB->linearDamping) / 2;
        double friction = (one->RB->m_angularDamping + two->RB->m_angularDamping) / 2;
        

        if (axe == bOneX || axe == bOneY || axe == bOneZ ||
            axe == bTwoX || axe == bTwoY || axe == bTwoZ)
        {
            // Collision Face-Point
            double penetration = std::min(intervalOne.max - intervalTwo.min, intervalTwo.max - intervalOne.min); // Pas sur
            
            Vector3D contactPoint;

            if (intervalOne.min < intervalTwo.min) {
                contactPoint = two->RB->position + (axe * intervalTwo.min);
            }
            else {
                contactPoint = one->RB->position + (axe * intervalOne.min);
            }
            
            //Vector3D contactPoint = intervalTwo.Vertice; //intervalOne.Vertice + (intervalTwo.Vertice - intervalOne.Vertice) / 2; // Ne marche pas
           // axe.normalize();
            
            RBContact newContact;
            axe.normalize();
            newContact.contactNormal = axe;
            newContact.contactPoint = contactPoint;
            newContact.penetration = penetration;
            newContact.restitution = restitution;
            newContact.friction = friction;
            newContact.RigidBodies[0] = one->RB;
            newContact.RigidBodies[1] = two->RB;
            if(penetration >= 1)    // ASupprimer
                return 0;
            if(penetration > 0)
                contactRegistry->contacts.push_back(newContact);
        }
        else 
        {
            // Collision Edge-Edge
            double penetration = std::min(intervalOne.max - intervalTwo.min, intervalTwo.max - intervalOne.min); // Pas sur

            // Les extrémités des segments de droite
            Vector3D P1 = one->RB->position + (bOneX * one->halfSize.x) - (bOneY * one->halfSize.y) - (bOneZ * one->halfSize.z);
            Vector3D Q1 = one->RB->position - (bOneX * one->halfSize.x) - (bOneY * one->halfSize.y) - (bOneZ * one->halfSize.z);
            Vector3D P2 = two->RB->position + (bTwoX * two->halfSize.x) - (bTwoY * two->halfSize.y) - (bTwoY * two->halfSize.z);
            Vector3D Q2 = two->RB->position - (bTwoX * two->halfSize.x) - (bTwoY * two->halfSize.y) - (bTwoY * two->halfSize.z);

            Vector3D contactPoint = findEdgeEdgeContact(P1, Q1, P2, Q2);

            axe.normalize();
            RBContact newContact;
            newContact.contactNormal = axe;
            newContact.contactPoint = contactPoint;
            newContact.penetration = penetration;
            newContact.restitution = restitution;
            newContact.friction = friction;
            newContact.RigidBodies[0] = one->RB;
            newContact.RigidBodies[1] = two->RB;
            if (penetration >= 1)    // ASupprimer
                return 0;
            if (penetration > 0)
                contactRegistry->contacts.push_back(newContact);
               
        }
        
	}

    
    // Si fait partie des 6 axe principaux c'est un Point-Face sinon c'est un Edge-Edge
    // 6 Axes Principaux = X,Y,Z de chaque boite et les 9 autres axes = X*y, X*z,X*X ; Y*Y, Y*X,Y*Z ; ect...
    // En enlevant les doublons on obtient 15 axes

    // Ensuite on fait la projection des boites sur chaque axes et on calcule l'interpénetration.
    // On garde seulement les axes qui ont une interpénetration la plus petite possible.
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

Vector3D RBContactGenerator::findEdgeEdgeContact(Vector3D& P1, Vector3D& Q1, Vector3D& P2, Vector3D& Q2)
{
    Vector3D edge1 = Q1 - P1;
    Vector3D edge2 = Q2 - P2;
    Vector3D d = P2 - P1;

    // Calcul du dénominateur
    double denom = edge1.produitVectoriel(edge2).magnitude() * edge1.produitVectoriel(edge2).magnitude();

    // Calcul des coefficients
    double t1 = (d.produitVectoriel(edge2).produitScalaire(edge2.produitVectoriel(edge1))) / denom;
    double t2 = (d.produitVectoriel(edge1).produitScalaire(edge1.produitVectoriel(edge2))) / denom;

    // Calcul du point de contact
    Vector3D contactPoint = P1 + edge1 * t1;

    return contactPoint;
}
