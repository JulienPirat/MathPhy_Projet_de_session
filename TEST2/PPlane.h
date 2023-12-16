#pragma once
#include "Primitive.h"
#include "Vector3D.h"

class PPlane : public Primitive {
public:
	PPlane(Vector3D normal, RigidBody* RB, Matrix4 offset, double HalfX, double HalfY) : Primitive(RB, offset), normal(normal), halfsizeX(HalfX), halfsizeY(HalfY){
	}

	// vecteur perpendiculaire à la surface du plan
	Vector3D normal;

	//Halfsize
	double halfsizeX;
	double halfsizeY;

	// décalage du plan par rapport à l'origine
	double offsetP = 0; // Déjà dans Primitive ?
};