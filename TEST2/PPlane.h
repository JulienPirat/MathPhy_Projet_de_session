#pragma once
#include "Primitive.h"
#include "Vector3D.h"

class PPlane : public Primitive {
public:
	PPlane(Vector3D normal, RigidBody* RB, Matrix4 offset, float HalfX, float HalfY) : Primitive(RB, offset), normal(normal), halfsizeX(HalfX), halfsizeY(HalfY){
	}

	// vecteur perpendiculaire à la surface du plan
	Vector3D normal;

	//Halfsize
	float halfsizeX;
	float halfsizeY;

	// décalage du plan par rapport à l'origine
	float offsetP = 0.0f; // Déjà dans Primitive ?
};