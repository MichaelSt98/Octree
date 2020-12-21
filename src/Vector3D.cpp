//
// Created by Michael Staneker on 21.12.20.
//

#include "../include/Vector3D.h"


Vector3D::Vector3D(float _x, float _y, float _z)
        :x(_x), y(_y), z(_z) {

}

float& Vector3D::operator[](unsigned int i) {
    return D[i];
}

const float& Vector3D::operator[](unsigned int i) const {
    return D[i];
}

float Vector3D::maxComponent() const {
    float r = x;
    if(y>r) r = y;
    if(z>r) r = z;
    return r;
}

float Vector3D::minComponent() const {
    float r = x;
    if(y<r) r = y;
    if(z<r) r = z;
    return r;
}

Vector3D Vector3D::operator+(const Vector3D& r) const {
    return Vector3D(x+r.x, y+r.y, z+r.z);
}

Vector3D Vector3D::operator-(const Vector3D& r) const {
    return Vector3D(x-r.x, y-r.y, z-r.z);
}

Vector3D Vector3D::cmul(const Vector3D& r) const {
    return Vector3D(x*r.x, y*r.y, z*r.z);
}

Vector3D Vector3D::cdiv(const Vector3D& r) const {
    return Vector3D(x/r.x, y/r.y, z/r.z);
}

Vector3D Vector3D::operator*(float r) const {
    return Vector3D(x*r,y*r,z*r);
}


Vector3D Vector3D::operator/(float r) const {
    return Vector3D(x/r, y/r, z/r);
}

Vector3D& Vector3D::operator+=(const Vector3D& r) {
    x+=r.x;
    y+=r.y;
    z+=r.z;
    return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D& r) {
    x-=r.x;
    y-=r.y;
    z-=r.z;
    return *this;
}

Vector3D& Vector3D::operator*=(float r) {
    x*=r; y*=r; z*=r;
    return *this;
}

// Inner/dot product
float Vector3D::operator*(const Vector3D& r) const {
    return x*r.x + y*r.y + z*r.z;
}

float Vector3D::norm() const {
    return sqrtf(x*x+y*y+z*z);
}

float Vector3D::normSquared() const {
    return x*x + y*y + z*z;
}

// Cross product
Vector3D Vector3D::operator^(const Vector3D& r) const {
    return Vector3D(
            y * r.z - z * r.y,
            z * r.x - x * r.z,
            x * r.y - y * r.x
    );
}

Vector3D Vector3D::normalized() const {
    return *this / norm();
}
