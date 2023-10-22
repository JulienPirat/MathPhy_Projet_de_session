#include "ParticleContactResting.h"

void ParticleContactResting::Init(float deltaTime)
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
                    std::cout << "Collision ! Distance : " << distance << " | Position PA : x: " << ParticleA->getPosition().x << " ,y :" << ParticleA->getPosition().y <<
                        " | Position PB : x: " << ParticleB->getPosition().x << " ,y :" << ParticleB->getPosition().y <<
                        " | Restitution : " << restitution << " | Penetration : " << penetration << std::endl;

                    normalContact.afficher();
                    ParticleContact* PContact = new ParticleContact();
                    PContact->contactNormal = normalContact;
                    PContact->penetration = penetration;
                    PContact->restitution = restitution;
                    PContact->particle[0] = ParticleA;
                    PContact->particle[1] = ParticleB;
                    addContact(PContact, 1);
                }
            }
        }
    }
}

unsigned int ParticleContactResting::addContact(ParticleContact* contact, unsigned int limit) const
{

    if (contact->particle[0]->getVelocity().x == 0 && contact->particle[0]->getVelocity().z == 0) {
        if (contact->particle[0]->getVelocity().y >= -10 && contact->particle[0]->getVelocity().y < 0) {
            contact->particle[0]->setVelocity(Vector3D(0,0,0));
            contact->particle[0]->isResting = true;
        }
    }
    
    return 0;
}
