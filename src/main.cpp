#include <cstdlib>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>

#include "../include/SimpleOctree.h"
#include "../include/Timer.h"

// Used for testing
std::vector<Vector3D> points;
SimpleOctree *octree;
SimpleOctreePoint *octreePoints;
Vector3D qmin, qmax;

// Random number between [-1,1]
float rand11() {
    return -1.f + (2.f*rand()) * (1.f / RAND_MAX);
}

// Random vector with components in the range [-1,1]
Vector3D randVector3D() {// Random vector with components in the range [-1,1]
    return Vector3D(rand11(), rand11(), rand11());
}

// Determine if 'point' is within the bounding box [bmin, bmax]
bool naivePointInBox(const Vector3D& point, const Vector3D& bmin, const Vector3D& bmax) {
    return
            point.x >= bmin.x &&
            point.y >= bmin.y &&
            point.z >= bmin.z &&
            point.x <= bmax.x &&
            point.y <= bmax.y &&
            point.z <= bmax.z;
}

void init() {
    // Create a new Octree centered at the origin
    // with physical dimension 2x2x2
    octree = new SimpleOctree(Vector3D(0,0,0), Vector3D(1,1,1));

    // Create a bunch of random points
    const int nPoints = 1 * 1000 * 1000;
    for(int i=0; i<nPoints; ++i) {
        points.push_back(randVector3D());
    }
    std::cout << "Create points: " << points.size() << std::endl;

    // Insert the points into the octree
    octreePoints = new SimpleOctreePoint[nPoints];
    for(int i=0; i<nPoints; ++i) {
        octreePoints[i].setPosition(points[i]);
        octree->insert(octreePoints + i);
    }
    std::cout << "Inserted points to octree" << std::endl;

    // Create a very small query box. The smaller this box is
    // the less work the octree will need to do. This may seem
    // like it is exagerating the benefits, but often, we only
    // need to know very nearby objects.
    qmin = Vector3D(-.05,-.05,-.05);
    qmax = Vector3D(.05,.05,.05);

    // Remember: In the case where the query is relatively close
    // to the size of the whole octree space, the octree will
    // actually be a good bit slower than brute forcing every point!
}

// Query using brute-force
void testNaive() {
    Timer t;

    std::vector<int> results;
    for(int i=0; i<points.size(); ++i) {
        if(naivePointInBox(points[i], qmin, qmax)) {
            results.push_back(i);
        }
    }

    std::cout << "Time elapsed for testNaive(): " << t.elapsed() << std::endl;
}

// Query using Octree
void testOctree() {
    Timer t;

    std::vector<SimpleOctreePoint*> results;
    octree->getPointsInsideBox(qmin, qmax, results);

    std::cout << "Time elapsed for testOctree(): " << t.elapsed() << std::endl;
}


int main(int argc, char **argv) {
    init();
    testNaive();
    testOctree();

    return 0;
}