#include "ParticleContactResting.h"

unsigned int ParticleContactResting::addContact(ParticleContactRegistry* ContactRegistry, unsigned int limit) const
{
    for (auto ParticleA : particle) {
        for (auto ParticleB : particle) {
            if (ParticleA != ParticleB) {

                double dx = ParticleA->getPosition().x - ParticleB->getPosition().x;
                double dy = ParticleA->getPosition().y - ParticleB->getPosition().y;
                double distance = sqrt((dx * dx) + (dy * dy));

                if (distance < radius * 2) {
                    double restitution = (ParticleA->getDamping() + ParticleB->getDamping()) / 2;
                    double penetration = ((radius * 2) - distance);
                    Vector3D normalContact = ParticleA->getPosition() - ParticleB->getPosition();
                    normalContact.norme();
                    //std::cout << "Collision ! Distance : " << distance << " | Position PA : x: " << ParticleA->getPosition().x << " ,y :" << ParticleA->getPosition().y <<
                    //    " | Position PB : x: " << ParticleB->getPosition().x << " ,y :" << ParticleB->getPosition().y <<
                    //    " | Restitution : " << restitution << " | Penetration : " << penetration << std::endl;

                    //normalContact.afficher();
                    
                    if (ParticleB->getInverseMass() < 0) {
                        if (ParticleA->getVelocity().x == 0 && ParticleA->getVelocity().z == 0) {
                            if (ParticleA->getVelocity().y >= -10 && ParticleA->getVelocity().y < 0) {

                                // Si on collide un sol avec une masse infini

                                ParticleA->setVelocity(Vector3D(0, 0, 0));
                                //ParticleA->isResting = true; //Pas utilisé
                            }
                        }
                    }
                }
            }
        }
    }
    
    return limit;
}
