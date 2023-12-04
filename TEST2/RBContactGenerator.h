#pragma once
#include "PSphere.h"
#include "PPlane.h"
#include <RBContactRegistry.h>
#include <PBox.h>


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
	unsigned boxAndPlane(
		PBox* box,
		PPlane* plane,
		RBContactRegistry* contactRegistry
	);
	unsigned boxAndSphere(
		PBox* box,
		PSphere* sphere,
		RBContactRegistry* contactRegistry
	);
};