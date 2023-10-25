#include "ParticleContactRegistry.h"

void ParticleContactRegistry::DetectContact(std::vector<Particle*>& particles)
{
    for (auto ParticleA : particles) {
        for (auto ParticleB : particles) {
            if (ParticleA != ParticleB) {

                //Get distance between particle
                float dx = ParticleA->getPosition().x - ParticleB->getPosition().x;
                float dy = ParticleA->getPosition().y - ParticleB->getPosition().y;
                float distance = sqrt((dx * dx) + (dy * dy));

                //Detect if Contact Resting


                //Detect if Contact Wall


                //Detect if Naive





                if (distance < radius * 2) {
                    float restitution = (ParticleA->getDamping() + ParticleB->getDamping()) / 2;
                    float penetration = radius * 2 - ((radius * 2) - distance);
                    Vector3D normalContact = ParticleA->getPosition() - ParticleB->getPosition();
                    normalContact.norme();
                    //std::cout << "Collision ! Distance : " << distance << " | Position PA : x: " << ParticleA->getPosition().x << " ,y :" << ParticleA->getPosition().y <<
                    //    " | Position PB : x: " << ParticleB->getPosition().x << " ,y :" << ParticleB->getPosition().y <<
                    //    " | Restitution : "<< restitution << " | Penetration : " << penetration << std::endl;

                    //normalContact.afficher();
                    ParticleContact PContact;
                    PContact.contactNormal = normalContact;
                    PContact.penetration = penetration;
                    PContact.restitution = restitution;
                    PContact.particle[0] = ParticleA;
                    PContact.particle[1] = ParticleB;
                    //PContact.resolve(deltaTime);

                    if (!PContact.particle[0]->isResting) {
                        PContact.resolve(deltaTime);
                    }

                }
            }
        }
    }
}

void ParticleContactRegistry::ClearContactRegistry()
{
}
