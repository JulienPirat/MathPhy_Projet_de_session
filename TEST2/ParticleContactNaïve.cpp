#include "ParticleContactNaïve.h"
void ParticleContactNaïve::Init()
{
    for (auto ParticleA : particle) {
        for (auto ParticleB : particle) {
            if (ParticleA != ParticleB) {
                float dx = ParticleA->getPosition().x - ParticleB->getPosition().x;
                float dy = ParticleA->getPosition().y - ParticleB->getPosition().y;
                float distance = sqrt((dx * dx) + (dy * dy));

                if (distance < radius * 2) {
                    float restitution = (radius * 2 - distance)/(radius*2); //pas sur de la formule
                    float penetration = radius*2-((radius * 2) - distance);
                    //Vector3D normalContact = ParticleA->getVelocity();
                    std::cout << "Collision ! Distance : " << distance << " | Position PA : x: " << ParticleA->getPosition().x << " ,y :" << ParticleA->getPosition().y <<
                        " | Position PB : x: " << ParticleB->getPosition().x << " ,y :" << ParticleB->getPosition().y <<
                        " | Restitution : "<< restitution << " | Penetration : " << penetration << std::endl;
                    
                    //ParticleContact PContact = new ParticleContact();
                }
            }
        }
    }
}

/*
ParticleContactNaïve::ParticleContactNaïve(std::vector<Particle*> _particle, float _radius)
{
    this->particle = _particle;
    this->radius = _radius;

    //TODO CHECK Interpenetration
}
*/
unsigned int ParticleContactNaïve::addContact(ParticleContact* contact, unsigned int limit) const
{
    return 0;
}
