#include "../include/SimpleOctree.h"


SimpleOctree::SimpleOctree(const Vector3D& origin, const Vector3D& halfDimension)
        : origin(origin), halfDimension(halfDimension), data(NULL) {
    // Initially, there are no children
    for(int i=0; i<8; ++i)
        children[i] = NULL;
}

SimpleOctree::SimpleOctree(const SimpleOctree& copy)
        : origin(copy.origin), halfDimension(copy.halfDimension), data(copy.data) {

}

SimpleOctree::~SimpleOctree() {
    // Recursively destroy octants
    for(int i=0; i<8; ++i)
        delete children[i];
}

int SimpleOctree::getOctantContainingPoint(const Vector3D& point) const {
    int oct = 0;
    if(point.x >= origin.x) oct |= 4;
    if(point.y >= origin.y) oct |= 2;
    if(point.z >= origin.z) oct |= 1;
    return oct;
}

bool SimpleOctree::isLeafNode() const {
    // This is correct, but overkill. See below.
    /*
         for(int i=0; i<8; ++i)
         if(children[i] != NULL)
         return false;
         return true;
     */

    // We are a leaf iff we have no children. Since we either have none, or
    // all eight, it is sufficient to just check the first.
    return children[0] == NULL;
}

void SimpleOctree::insert(SimpleOctreePoint* point) {

    if(isLeafNode()) {
        if(data==NULL) {
            data = point;
            return;
        } else {
            // We're at a leaf, but there's already something here
            // We will split this node so that it has 8 child octants
            // and then insert the old data that was here, along with
            // this new data point

            // Save this data point that was here for a later re-insert
            SimpleOctreePoint *oldPoint = data;
            data = NULL;

            // Split the current node and create new empty trees for each
            // child octant.
            for(int i=0; i<8; ++i) {
                // Compute new bounding box for this child
                Vector3D newOrigin = origin;
                newOrigin.x += halfDimension.x * (i&4 ? .5f : -.5f);
                newOrigin.y += halfDimension.y * (i&2 ? .5f : -.5f);
                newOrigin.z += halfDimension.z * (i&1 ? .5f : -.5f);
                children[i] = new SimpleOctree(newOrigin, halfDimension*.5f);
            }

            // Re-insert the old point, and insert this new point
            // (We wouldn't need to insert from the root, because we already
            // know it's guaranteed to be in this section of the tree)
            children[getOctantContainingPoint(oldPoint->getPosition())]->insert(oldPoint);
            children[getOctantContainingPoint(point->getPosition())]->insert(point);
        }
    } else {
        // We are at an interior node. Insert recursively into the
        // appropriate child octant
        int octant = getOctantContainingPoint(point->getPosition());
        children[octant]->insert(point);
    }
}


void SimpleOctree::getPointsInsideBox(const Vector3D& bmin, const Vector3D& bmax, std::vector<SimpleOctreePoint*>& results) {
    // If we're at a leaf node, just see if the current data point is inside
    // the query bounding box
    if(isLeafNode()) {
        if(data!=NULL) {
            const Vector3D& p = data->getPosition();
            if(p.x>bmax.x || p.y>bmax.y || p.z>bmax.z) return;
            if(p.x<bmin.x || p.y<bmin.y || p.z<bmin.z) return;
            results.push_back(data);
        }
    } else {
        // We're at an interior node of the tree. We will check to see if
        // the query bounding box lies outside the octants of this node.
        for(int i=0; i<8; ++i) {
            // Compute the min/max corners of this child octant
            Vector3D cmax = children[i]->origin + children[i]->halfDimension;
            Vector3D cmin = children[i]->origin - children[i]->halfDimension;

            // If the query rectangle is outside the child's bounding box,
            // then continue
            if(cmax.x<bmin.x || cmax.y<bmin.y || cmax.z<bmin.z) continue;
            if(cmin.x>bmax.x || cmin.y>bmax.y || cmin.z>bmax.z) continue;

            // At this point, we've determined that this child is intersecting
            // the query bounding box
            children[i]->getPointsInsideBox(bmin,bmax,results);
        }
    }
}

