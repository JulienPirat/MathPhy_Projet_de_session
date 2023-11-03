#pragma once
#include <RigidBody.h>
#include <RBForceGenerator.h>
#include <vector>

class RBForceRegistry
{
protected:

	///Attributes

	struct RBForceRegistration
	{
		RigidBody* rigidbody;
		RBForceGenerator* RBforceGenerator;
	};

	using Registry = std::vector<RBForceRegistration>;
	Registry m_registery;

public:

	///Methodes

	/**
	* Registers the given force generator to apply to the
	* given rigidbody.
	*/
	void add(RigidBody* rigidbody, RBForceGenerator* fg);

	/**
	* Removes the given registered pair from the registry.
	* If the pair is not registered, this method will have
	* no effect.
	*/
	void remove(RigidBody* rigidbody, RBForceGenerator* fg);

	/**
	* Clears all registrations from the registry. This will
	* not delete the rigidbodys or the force generators
	* themselves, just the records of their connection.
	*/
	void clear();

	/**
	* Calls all the force generators to update the forces of
	* their corresponding rigidBodys.
	*/
	void UpdateForce();

};