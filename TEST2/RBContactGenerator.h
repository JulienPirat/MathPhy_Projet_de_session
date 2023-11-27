#pragma once
#include "PSphere.h"
#include <RBContactRegistry.h>


class ContactGenerator
{

public:
	unsigned sphereAndSphere(
		PSphere* one,
		PSphere* two,
		RBContactRegistry* contactRegistry
		);
};