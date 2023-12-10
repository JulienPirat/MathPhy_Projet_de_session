#include "KDTRee.h"
#include <algorithm>

///Generate
// - Current Depth of the tree
// - List of our rigibodies remains to be dispatch
// - Next Axis the next axis used to separate the rigidbodies
BaseNode* KDTRee::generateTree(int currentDepth, std::vector<RigidBody*> RBList, Axis axis)
{
    //Check if we need to create a leaf or a PlaneDivision
    if (currentDepth >= MAX_DEPTH || RBList.size() < 1) {
        //On return une leaf
        return new Leaf(RBList);
    }
    else {
        //On trie la liste en fonction de l'axe de s�paration
        switch (axis) {
        case Axis::X:
            // X
            std::sort(RBList.begin(), RBList.end(), cmpX);
            break;
        case Axis::Y:
            // Y
            std::sort(RBList.begin(), RBList.end(), cmpY);
            break;
        case Axis::Z:
            // Z
            std::sort(RBList.begin(), RBList.end(), cmpZ);
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
        Plane seperatePlane = Plane(newAxis, mediane);

        std::size_t const half_size = RBList.size();
        std::vector<RigidBody*> RBListRight(RBList.begin(), RBList.begin() + half_size);
        std::vector<RigidBody*> RBListLeft(RBList.begin() + half_size, RBList.end());


        //Generate branches
        return new PlaneDivision(seperatePlane, generateTree(currentDepth + 1, RBListLeft, newAxis), generateTree(currentDepth + 1, RBListRight, newAxis));

    }
}

std::vector<std::pair<RigidBody*, RigidBody*>> KDTRee::getPotentialCollisions(BaseNode* base)
{
    //Notre liste de collisions qui seront a tester
    std::vector < std::pair<RigidBody*, RigidBody*>> potentialCollisionList;

    /**/

    return std::vector<std::pair<RigidBody*, RigidBody*>>();
}

PlaneDivision getNearestPoint(RigidBody* actualpoint) {

}

bool KDTRee::cmpX(const RigidBody& a, const RigidBody& b)
{
    return a.position.x <= b.position.x;
}

bool KDTRee::cmpY(const RigidBody& a, const RigidBody& b)
{
    return a.position.y <= b.position.y;
}

bool KDTRee::cmpZ(const RigidBody& a, const RigidBody& b)
{
    return a.position.z <= b.position.z;
}