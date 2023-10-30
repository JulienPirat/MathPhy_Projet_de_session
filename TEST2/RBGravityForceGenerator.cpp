#include "RBGravityForceGenerator.h"

void RBGravityForceGenerator::UpdateForce(RigidBody* rigidBody)
{
	//TODO si rigidBody masse Infini return;

	m_gravity.operator*=(rigidBody->inverseMasse);

	rigidBody->AddForce(m_gravity);
}
