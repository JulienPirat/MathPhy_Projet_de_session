#pragma once

#include <RigidBody.h>
#include <vector>

enum Axis
{
	X = 0,
	Y = 1,
	Z = 2,
};

struct Plane
{
	Axis axis;
	float coordinate;

	Plane() {
		axis = Axis::X;
		coordinate = 0;
	}

	Plane(Axis ax, float coord) {
		axis = ax;
		coordinate = coord;
	}
};

struct Node {
	Plane plane;
	Node* left;
	Node* right;
	std::vector<RigidBody*> body;

	Node() = delete;

	Node(Plane pl, Node* l, Node* r) : plane(pl), left(l), right(r) {

	}

	Node(std::vector<RigidBody*> b) : body(b) {

	}
};

class KDTRee
{
	static const int MAX_DEPTH = 10;

	std::vector<std::pair<RigidBody*, RigidBody*>> getPotentialCollisions(Node* base);
	static Node* generateTree(int currentDepth, std::vector<RigidBody*> RBList, Axis axis);
	Node* getNearestPoint(RigidBody* actualpoint, Node* currentNode, RigidBody* refpoint, float distanceBetweenPt);

	bool cmpX(const RigidBody& a, const RigidBody& b);
	bool cmpY(const RigidBody& a, const RigidBody& b);
	bool cmpZ(const RigidBody& a, const RigidBody& b);
};

