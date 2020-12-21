//
// Created by Michael Staneker on 21.12.20.
//

#ifndef OCTREE_VECTOR3D_H
#define OCTREE_VECTOR3D_H

#include <cmath>

class Vector3D;
Vector3D operator*(float r, const Vector3D& v);

class Vector3D {
public:
    union {
        struct {
            float x,y,z;
        };
        float D[3];
    };

    Vector3D() { }
    Vector3D(float _x, float _y, float _z);

    float& operator[](unsigned int i);

    const float& operator[](unsigned int i) const;

    float maxComponent() const;

    float minComponent() const;

    Vector3D operator+(const Vector3D& r) const;

    Vector3D operator-(const Vector3D& r) const;

    Vector3D cmul(const Vector3D& r) const;

    Vector3D cdiv(const Vector3D& r) const;

    Vector3D operator*(float r) const;

    Vector3D operator/(float r) const;

    Vector3D& operator+=(const Vector3D& r);

    Vector3D& operator-=(const Vector3D& r);

    Vector3D& operator*=(float r);

    // Inner/dot product
    float operator*(const Vector3D& r) const;

    float norm() const;

    float normSquared() const;

    // Cross product
    Vector3D operator^(const Vector3D& r) const;

    Vector3D normalized() const;
};

inline Vector3D operator*(float r, const Vector3D& v) {
    return Vector3D(v.x*r, v.y*r, v.z*r);
}

#endif //OCTREE_VECTOR3D_H
