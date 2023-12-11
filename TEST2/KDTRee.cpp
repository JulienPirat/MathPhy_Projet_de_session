#include "KDTRee.h"
#include <algorithm>

///Generate
// - Current Depth of the tree
// - List of our rigibodies remains to be dispatch
// - Next Axis the next axis used to separate the rigidbodies
Node* KDTRee::generateTree(int currentDepth, std::vector<RigidBody*> RBList, Axis axis)
{
    //Check if we need to create a leaf or a PlaneDivision
    if (currentDepth >= MAX_DEPTH || RBList.size() <= 1) {
        //On return une leaf
        return new Node(RBList);
    }
    else {
        //On trie la liste en fonction de l'axe de s�paration
        switch (axis) {
        case Axis::X:
            // X
            std::sort(RBList.begin(), RBList.end(), [](RigidBody* a, RigidBody* b) {return a->position.x < b->position.x; });
            break;
        case Axis::Y:
            // Y
            std::sort(RBList.begin(), RBList.end(), [](RigidBody* a, RigidBody* b) {return a->position.y < b->position.y; });
            break;
        case Axis::Z:
            // Z
            std::sort(RBList.begin(), RBList.end(), [](RigidBody* a, RigidBody* b) {return a->position.z < b->position.z; });
            break;
        default:
            // ERROR
            break;
        }

        //Calcul de la m�diane
        float mediane = 0;
        Vector3D positionMediane;

        if (RBList.size() % 2 == 0)
        {
            //Nombre d'elements pairs on prends donc la moyenne des elements au centre
            int i = RBList.size() / 2;
            positionMediane = (RBList.at(i - 1)->position + RBList.at(i)->position) / 2;
        }
        else {
            //Nombre d'elements impairs on prends donc l'element au centre
            positionMediane = RBList.at(RBList.size() / 2)->position;
        }

        //Definir nouvel Axis
        Axis newAxis;

        //Definir la m�diane
        switch (axis) {
        case Axis::X:
            // X
            mediane = positionMediane.x;
            newAxis = Axis::Y;
            break;
        case Axis::Y:
            // Y
            mediane = positionMediane.y;
            newAxis = Axis::Z;
            break;
        case Axis::Z:
            // Z
            mediane = positionMediane.z;
            newAxis = Axis::X;
            break;
        default:
            // ERROR
            break;
        }

        //Seperate list
        PlaneDiv seperatePlane = PlaneDiv(newAxis, mediane);

        std::size_t const half_size = RBList.size() / 2;
        std::vector<RigidBody*> RBListRight(RBList.begin(), RBList.begin() + half_size);
        std::vector<RigidBody*> RBListLeft(RBList.begin() + half_size, RBList.end());


        //Generate branches
        return new Node(seperatePlane, generateTree(currentDepth + 1, RBListLeft, newAxis), generateTree(currentDepth + 1, RBListRight, newAxis));

    }
}

std::vector<std::pair<RigidBody*, RigidBody*>> KDTRee::getPotentialCollisions(std::vector<RigidBody*> RBList, Node* root)
{
    //Notre liste de collisions qui seront a tester
    std::vector < std::pair<RigidBody*, RigidBody*>> potentialCollisionList;


    for (auto rb : RBList) {
        RigidBody* outNearestRB = nullptr;
        float currentDistanceBtw = 10000000;

        RigidBody* rbtemp = KDTRee::getNearestPoint(rb, root, outNearestRB, &currentDistanceBtw);

        bool canBeAdd = true;
        for (auto pair: potentialCollisionList) {
            if ((pair.first == rbtemp && pair.second == rb)) {
                canBeAdd = false;
                break;
            }
        }

        //On check si les deux rigidbodies sont bien non nuls
        canBeAdd = canBeAdd && rbtemp != nullptr && rb != nullptr;

        if (canBeAdd) {
            potentialCollisionList.push_back(std::pair<RigidBody*, RigidBody*>(rb, rbtemp));
        }
    }

    return potentialCollisionList;
}

RigidBody* KDTRee::getNearestPoint(RigidBody* actualpoint, Node* currentNode, RigidBody* refpoint, float* currentDistanceBtw) {

    //Check if leaf == dead end
    if (currentNode->left == nullptr && currentNode->right == nullptr) {
        //on check la distance absolue de ce nouveau point
        RigidBody* reftosend = nullptr;
        for (auto rbtocheck : currentNode->body) {
            if (rbtocheck != actualpoint)
            {
                float newDistanceBetweenPt = (actualpoint->position - rbtocheck->position).magnitude();
                if (newDistanceBetweenPt < *currentDistanceBtw) {
                    *currentDistanceBtw = newDistanceBetweenPt;
                    reftosend = rbtocheck;
                }
            }
        }
        return reftosend;
    }
    else {

        //L'axe de separation
        float actualpointaxisval = 0;

        switch (currentNode->plane.axis) {
        case Axis::X:
            actualpointaxisval = actualpoint->position.x;
            break;
        case Axis::Y:
            actualpointaxisval = actualpoint->position.y;
            break;
        case Axis::Z:
            actualpointaxisval = actualpoint->position.z;
            break;
        }

        bool searchFirstLeft;
        if (actualpointaxisval <= currentNode->plane.coordinate) {
            searchFirstLeft = true;
        }
        else {
            searchFirstLeft = false;
        }

        RigidBody* rbRight = nullptr;
        RigidBody* rbLeft = nullptr;

        if (searchFirstLeft == true) {
            if (actualpointaxisval - *currentDistanceBtw <= currentNode->plane.coordinate) {
                rbLeft = getNearestPoint(actualpoint, currentNode->left,refpoint, currentDistanceBtw);
            }
            if (actualpointaxisval + *currentDistanceBtw > currentNode->plane.coordinate) {
                 rbRight = getNearestPoint(actualpoint, currentNode->right, refpoint, currentDistanceBtw);
            }
        }
        else {
            if (actualpointaxisval + *currentDistanceBtw > currentNode->plane.coordinate) {
                rbRight = getNearestPoint(actualpoint, currentNode->right, refpoint, currentDistanceBtw);
            }
            if (actualpointaxisval - *currentDistanceBtw <= currentNode->plane.coordinate) {
                rbLeft = getNearestPoint(actualpoint, currentNode->left, refpoint, currentDistanceBtw);
            }
        }

        switch (currentNode->plane.axis)
        {
        case Axis::X:
            if (rbLeft != nullptr && rbRight != nullptr) {
                if (abs(actualpoint->position.x - rbLeft->position.x) < abs(actualpoint->position.x - rbRight->position.x)) {
                    return rbLeft;
                }
                else {
                    return rbRight;
                }
            }
            else if (rbLeft != nullptr) {
                return rbLeft;
            }
            else if (rbRight != nullptr) {
                return rbRight;
            }
            break;
        case Axis::Y:
            if (rbLeft != nullptr && rbRight != nullptr) {
                if (abs(actualpoint->position.y - rbLeft->position.y) < abs(actualpoint->position.y - rbRight->position.y)) {
					return rbLeft;
				}
                else {
					return rbRight;
				}
			}
            else if (rbLeft != nullptr) {
				return rbLeft;
			}
            else if (rbRight != nullptr) {
				return rbRight;
			}
            break;
        case Axis::Z:
            if (rbLeft != nullptr && rbRight != nullptr) {
				if (abs(actualpoint->position.z - rbLeft->position.z) < abs(actualpoint->position.z - rbRight->position.z)) {}
            }
            else if (rbLeft != nullptr) {
                return rbLeft;
            }
            else if (rbRight != nullptr) {
                return rbRight;
			}
            break;
        }
    }

}

void KDTRee::deleteTree(Node* base)
{
    if (base != nullptr) {
        if (base->left != nullptr) {
            deleteTree(base->left);
        }
        if (base->right != nullptr) {
            deleteTree(base->right);
        }
		delete base;
	}
}