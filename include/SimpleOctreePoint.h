//
// Created by Michael Staneker on 21.12.20.
//

#ifndef OCTREE_SIMPLEOCTREEPOINT_H
#define OCTREE_SIMPLEOCTREEPOINT_H

#include "Vector3D.h"

// Simple point data type to insert into the tree.
// Have something with more interesting behavior inherit
// from this in order to store other attributes in the tree.
class SimpleOctreePoint {
    Vector3D position;
public:
    SimpleOctreePoint();
    SimpleOctreePoint(const Vector3D& position);
    const Vector3D& getPosition() const;
    void setPosition(const Vector3D& p);
};


#endif //OCTREE_SIMPLEOCTREEPOINT_H
