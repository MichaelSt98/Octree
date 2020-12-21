#include "../include/SimpleOctreePoint.h"


SimpleOctreePoint::SimpleOctreePoint() {

}

SimpleOctreePoint::SimpleOctreePoint(const Vector3D& position) :
            position(position) {

}

const Vector3D& SimpleOctreePoint::getPosition() const {
    return position;
}

void SimpleOctreePoint::setPosition(const Vector3D& p) {
    position = p;
}

