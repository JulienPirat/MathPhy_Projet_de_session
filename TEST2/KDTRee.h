#pragma once

#include <RigidBody.h>
#include <vector>

enum Axis
{
	X = 0,
	Y = 1,
	Z = 2,
};

struct PlaneDiv
{
	Axis axis;
	float coordinate;

	PlaneDiv() {
		axis = Axis::X;
		coordinate = 0;
	}

	PlaneDiv(Axis ax, float coord) {
		axis = ax;
		coordinate = coord;
	}
};

struct Node {
	PlaneDiv plane;
	Node* left = nullptr;
	Node* right = nullptr;
	std::vector<RigidBody*> body;

	Node() = delete;

	Node(PlaneDiv pl, Node* l, Node* r) : plane(pl), left(l), right(r) {

	}

	Node(std::vector<RigidBody*> b) : body(b) {

	}

	~Node() {
	}
};

class KDTRee
{
public:
	static const int MAX_DEPTH = 10;

	static std::vector<std::pair<RigidBody*, RigidBody*>> getPotentialCollisions(std::vector<RigidBody*> RBList, Node* root);
	static Node* generateTree(int currentDepth, std::vector<RigidBody*> RBList, Axis axis);
	static void getNearestPoint(RigidBody* actualpoint, Node* currentNode, RigidBody* refpoint, float distanceBetweenPt);

	static void deleteTree(Node* base);
};

