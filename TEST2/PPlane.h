#pragma once
#include "Primitive.h"
#include "Vector3D.h"

class PPlane : public Primitive {
public:
	PPlane(Vector3D normal, RigidBody* RB, Matrix4 offset, double HalfX, double HalfY) : Primitive(RB, offset), normal(normal), halfsizeX(HalfX), halfsizeY(HalfY){
	}

	// vecteur perpendiculaire � la surface du plan
	Vector3D normal;

	//Halfsize
	double halfsizeX;
	double halfsizeY;

	// d�calage du plan par rapport � l'origine
	double offset; // D�j� dans Primitive ?
};