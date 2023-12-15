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

class RBContactGenerator
{

public:
	static unsigned sphereAndSphere(
		PSphere* one,
		PSphere* two,
		RBContactRegistry* contactRegistry
		);

	static unsigned sphereAndPlane(
		PSphere* sphere,
		PPlane* plane,
		RBContactRegistry* contactRegistry
		);
	static unsigned boxAndPlane(
		PBox* box,
		PPlane* plane,
		RBContactRegistry* contactRegistry
	);
	static unsigned boxAndSphere(
		PBox* box,
		PSphere* sphere,
		RBContactRegistry* contactRegistry
	);
	static unsigned boxAndBox(
		PBox* one,
		PBox* two,
		RBContactRegistry* contactRegistry
	);

private:
	static Interval ProjectBoxOnAxis(PBox* box, Vector3D* axis);
};
