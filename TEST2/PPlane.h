#pragma once
#include "Primitive.h"
#include "Vector3D.h"

class PPlane : public Primitive {
public:
	PPlane(Vector3D normal, RigidBody* RB, Matrix4 offset) : Primitive(RB, offset), normal(normal) { }

	// vecteur perpendiculaire � la surface du plan
	Vector3D normal;

	// d�calage du plan par rapport � l'origine
	float offset; // D�j� dans Primitive ?
};