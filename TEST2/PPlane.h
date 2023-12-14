#pragma once
#include "Primitive.h"
#include "Vector3D.h"

class PPlane : public Primitive {
public:
	PPlane(Vector3D normal, RigidBody* RB, Matrix4 offset) : Primitive(RB, offset), normal(normal) { }

	// vecteur perpendiculaire à la surface du plan
	Vector3D normal;

	// décalage du plan par rapport à l'origine
	float offset; // Déjà dans Primitive ?
};