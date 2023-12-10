#pragma once
#include "PSphere.h"
#include "PPlane.h"
#include <RBContactRegistry.h>
#include <PBox.h>


struct Interval {
	double min;
	double max;
	Vector3D Vertice;
};

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
	unsigned boxAndBox(
		PBox* one,
		PBox* two,
		RBContactRegistry* contactRegistry
	);

private:
	Interval ProjectBoxOnAxis(PBox* box, Vector3D* axis);
};
