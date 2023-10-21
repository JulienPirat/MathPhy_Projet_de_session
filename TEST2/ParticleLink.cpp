#include "ParticleLink.h"

float ParticleLink::currentLength() const
{
	Vector3D relativePos = particle[0]->getPosition() -
		particle[1]->getPosition();

	return relativePos.magnitude();
}
