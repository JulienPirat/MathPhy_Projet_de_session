#pragma once
#include <ParticleLink.h>

class ParticleCable : public ParticleLink
{
	protected:

		///Attributs

		//a contact will be generated if the distance between the particles is larger than maxLength
		float maxLength;

		//bounciness of the cable
		float restitution;

	public:

		///COntructeurs

		ParticleCable(float mLength, float rest, Particle* p1, Particle* p2){
			maxLength = mLength;
			restitution = rest;
			particle[0] = p1;
			particle[1] = p2;
		}

		///Methodes

		//Fill information contact with informations from particles and contact generator
		unsigned int addContact(ParticleContactRegistry* ContactRegistry, unsigned int limit) const;

};

