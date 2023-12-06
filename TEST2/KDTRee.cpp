#include "KDTRee.h"

BaseNode* KDTRee::generateTree(int currentDepth, std::vector<RigidBody*>)
{
	return new Leaf();
}
