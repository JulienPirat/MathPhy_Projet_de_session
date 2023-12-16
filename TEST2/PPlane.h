#pragma once
#include "Primitive.h"
#include "Vector3D.h"

class PPlane : public Primitive {
public:
	PPlane(Vector3D normal, RigidBody* RB, Matrix4 offset, float HalfX, float HalfY) : Primitive(RB, offset), normal(normal), halfsizeX(HalfX), halfsizeY(HalfY){
	}

	// vecteur perpendiculaire � la surface du plan
	Vector3D normal;

	//Halfsize
	float halfsizeX;
	float halfsizeY;

	// d�calage du plan par rapport � l'origine
	float offsetP = 0.0f; // D�j� dans Primitive ?
};