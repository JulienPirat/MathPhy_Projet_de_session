#include "ParticleContactNaïve.h"

unsigned int ParticleContactNaïve::addContact(ParticleContactRegistry* ContactRegistry, unsigned int limit) const
{
    for (auto ParticleA : particle) {
        for (auto ParticleB : particle) {
            if (ParticleA != ParticleB) {
                float dx = ParticleA->getPosition().x - ParticleB->getPosition().x;
                float dy = ParticleA->getPosition().y - ParticleB->getPosition().y;
                float distance = sqrt((dx * dx) + (dy * dy));

                if (distance < radius * 2) {
                    float restitution = (ParticleA->getDamping() + ParticleB->getDamping()) / 2;
                    float penetration = radius * 2 - ((radius * 2) - distance);
                    Vector3D normalContact = ParticleA->getPosition() - ParticleB->getPosition();
                    normalContact.norme();
                    //std::cout << "Collision ! Distance : " << distance << " | Position PA : x: " << ParticleA->getPosition().x << " ,y :" << ParticleA->getPosition().y <<
                    //    " | Position PB : x: " << ParticleB->getPosition().x << " ,y :" << ParticleB->getPosition().y <<
                    //    " | Restitution : "<< restitution << " | Penetration : " << penetration << std::endl;

                    //normalContact.afficher();

                    // Création du contact
                    ParticleContact PContact;
                    PContact.contactNormal = normalContact;
                    PContact.penetration = penetration;
                    PContact.restitution = restitution;
                    PContact.particle[0] = ParticleA;
                    PContact.particle[1] = ParticleB;

                    // Ajoute le contact dans le registre des contacts
                    ContactRegistry->Contacts.push_back(PContact);
                    limit--;
                }
            }
        }
    }

    return limit;
}
