#include "RBForceGenerator.h"

class RBSpringForceGenerator : public RBForceGenerator {

private:

	// Anchor point in Local coordinate
	Vector3D m_bodyAnchor;

	// Other anchor point in other's Local coordinate
	Vector3D m_otherBodyAnchor;

	// If otherBodyAnchor in other RigidBody
	RigidBody* m_otherRigidBody = nullptr;

	// spring parameters
	float m_k; //Resistance du ressort
	float m_restLenght; //Taille du ressort

public:

	/// <summary>
	/// Constructeur
	/// </summary>
	/// <param name="bodyAnchor">Anchor point in Local coordinate</param>
	/// <param name="otherBodyAnchor">Other anchor point in other's Local coordinate</param>
	/// <param name="k">Resistance du ressort</param>
	/// <param name="restLength">Taille du ressort</param>
	/// <param name="otherRigidBody">If otherBodyAnchor in other RigidBody (can be nullptr)</param>
	RBSpringForceGenerator(Vector3D bodyAnchor, Vector3D otherBodyAnchor, float k, float restLength, RigidBody* otherRigidBody = nullptr) {
		m_k = k;
		m_restLenght = restLength;
		m_bodyAnchor = bodyAnchor;
		m_otherBodyAnchor = otherBodyAnchor;
		m_otherRigidBody = otherRigidBody;
	}

	// Transform each anchor point in world coordinate,
	// calculate the spring force and apply it at anchor point.
	void UpdateForce(RigidBody* rigidBody);
};