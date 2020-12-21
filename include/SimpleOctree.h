//
// Created by Michael Staneker on 21.12.20.
//

#ifndef OCTREE_SIMPLEOCTREE_H
#define OCTREE_SIMPLEOCTREE_H


#include <cstddef>
#include <vector>
#include "SimpleOctreePoint.h"

/**!
 *
 */
class SimpleOctree {

    Vector3D origin;         //! The physical center of this node
    Vector3D halfDimension;  //! Half the width/height/depth of this node

    SimpleOctree *children[8]; //! Pointers to child octants
    SimpleOctreePoint *data;   //! Data point to be stored at a node


public:
    SimpleOctree(const Vector3D& origin, const Vector3D& halfDimension);

    SimpleOctree(const SimpleOctree& copy);

    ~SimpleOctree();

    // Determine which octant of the tree would contain 'point'
    int getOctantContainingPoint(const Vector3D& point) const;

    bool isLeafNode() const;

    void insert(SimpleOctreePoint* point);

    // This is a really simple routine for querying the tree for points
    // within a bounding box defined by min/max points (bmin, bmax)
    // All results are pushed into 'results'
    void getPointsInsideBox(const Vector3D& bmin, const Vector3D& bmax, std::vector<SimpleOctreePoint*>& results);
};




#endif //OCTREE_SIMPLEOCTREE_H
