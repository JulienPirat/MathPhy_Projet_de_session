#pragma once
#include "RBForceGenerator.h"

class RBAnchoredSpringForceGenerator : public RBForceGenerator {

private:

	// Anchor point in Local coordinate
	Vector3D m_bodyAnchor;

	// Other anchor point in other's Local coordinate
	Vector3D m_WorldAnchor;

	// spring parameters
	float m_k; //Resistance du ressort
	float m_restLenght; //Taille du ressort

public:

	/// <summary>
	/// Constructeur
	/// </summary>
	/// <param name="bodyAnchor">Anchor point in Local coordinate</param>
	/// <param name="WorldAnchor">World Anchor Point</param>
	/// <param name="k">Resistance du ressort</param>
	/// <param name="restLength">Taille du ressort</param>
	/// <param name="otherRigidBody">If otherBodyAnchor in other RigidBody (can be nullptr)</param>
	RBAnchoredSpringForceGenerator(Vector3D bodyAnchor, Vector3D WorldAnchor, float k, float restLength) {
		m_k = k;
		m_restLenght = restLength;
		m_bodyAnchor = bodyAnchor;
		m_WorldAnchor = WorldAnchor;
	}

	// Transform each anchor point in world coordinate,
	// calculate the spring force and apply it at anchor point.
	void UpdateForce(RigidBody* rigidBody);
};

