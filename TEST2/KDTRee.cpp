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
        //On trie la liste en fonction de l'axe de séparation
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

        //Calcul de la médiane
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

        //Definir la médiane
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

        RigidBody* rbtemp = KDTRee::getNearestPoint(rb, root, outNearestRB, 10000000);

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

RigidBody* KDTRee::getNearestPoint(RigidBody* actualpoint, Node* currentNode, RigidBody* refpoint, float distanceBetweenPt) {

    //Check if leaf == dead end
    if (currentNode->left == nullptr && currentNode->right == nullptr) {
        //on check la distance absolue de ce nouveau point
        RigidBody* reftosend = nullptr;
        for (auto rbtocheck : currentNode->body) {
            if (rbtocheck != actualpoint)
            {
                float newDistanceBetweenPt = (actualpoint->position - rbtocheck->position).magnitude();
                if (newDistanceBetweenPt < distanceBetweenPt) {
                    distanceBetweenPt = newDistanceBetweenPt;
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

        if (searchFirstLeft == true) {
            if (actualpointaxisval - distanceBetweenPt <= currentNode->plane.coordinate) {
                return getNearestPoint(actualpoint, currentNode->left,refpoint,distanceBetweenPt);
            }
            if (actualpointaxisval + distanceBetweenPt > currentNode->plane.coordinate) {
                return getNearestPoint(actualpoint, currentNode->right, refpoint, distanceBetweenPt);
            }
        }
        else {
            if (actualpointaxisval + distanceBetweenPt > currentNode->plane.coordinate) {
                return getNearestPoint(actualpoint, currentNode->right, refpoint, distanceBetweenPt);
            }
            if (actualpointaxisval - distanceBetweenPt <= currentNode->plane.coordinate) {
                return getNearestPoint(actualpoint, currentNode->left, refpoint, distanceBetweenPt);
            }
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