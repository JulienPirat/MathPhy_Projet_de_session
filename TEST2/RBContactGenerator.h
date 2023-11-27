#pragma once
#include "PSphere.h"
#include "PPlane.h"
#include <RBContactRegistry.h>


class ContactGenerator
{

public:
	unsigned sphereAndSphere(
		PSphere* one,
		PSphere* two,
		RBContactRegistry* contactRegistry
		);

	unsigned sphereAndPlane(
		PSphere* sphere,
		PPlane* plane,
		RBContactRegistry* contactRegistry
		);
};