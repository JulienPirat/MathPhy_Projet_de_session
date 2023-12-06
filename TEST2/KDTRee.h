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
};

struct BaseNode { 
	BaseNode() = default; 
	virtual std::string toString() = 0;
};

struct Leaf : public BaseNode
{
	Leaf(std::vector<RigidBody*> listBodies) {
		body = listBodies;
	}

	std::vector<RigidBody*> body;

	std::string toString() override {
		std::string result = "Leaf: ";
		for (auto& b : body) {
			//TODO : add body to result
		}
		return result;
	}
};

struct PlaneDivision : public BaseNode
{
	Plane plane;
	BaseNode* left;
	BaseNode* right;

	PlaneDivision(Plane plane, BaseNode* left, BaseNode* right) {
		this->plane = plane;
		this->left = left;
		this->right = right;
	}

	std::string toString() override {
		std::string result = "PlaneDivision: ";
		//TODO : add plane to result
		//TODO : add left to result
		//TODO : add right to result
		return result;
	}
};

class KDTRee
{
	static const int MAX_DEPTH = 10;

	static BaseNode* generateTree(int currentDepth, std::vector<RigidBody*>);
};

