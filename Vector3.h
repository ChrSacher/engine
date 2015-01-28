#pragma once

#include <iostream>
#include <math.h>
#include <glew.h>

class Vector3
{
public:
        GLfloat vec[3];

        Vector3(void);
        Vector3(GLfloat x, GLfloat y, GLfloat z);
        Vector3(const GLfloat *v);
        Vector3(const Vector3 &v);
        Vector3& operator= (const Vector3& v);
        void set(GLfloat x, GLfloat y, GLfloat z);

        GLfloat& operator[](int i); //make vector treatable like an array
        GLfloat operator[](int i) const; 

		Vector3 operator+(const Vector3& v) const;
        Vector3 operator-(const Vector3& v) const;
        Vector3 operator*(GLfloat s) const;
        Vector3 operator/(GLfloat s) const;
        Vector3& operator+=(const Vector3& v);//add vector with + and save
        Vector3& operator-=(const Vector3& v);//sub vector with - and save
        Vector3& operator*=(GLfloat s);//mul vector with * and save
        Vector3& operator/=(GLfloat s);//div vector with / and save

        Vector3 operator-(void) const;
        bool operator==(const Vector3& v) const; //compare vectors
        bool operator!=(const Vector3& v) const;

        GLfloat distance(const Vector3& v) const;//distance between 2 Vectors
        GLfloat distanceSquared(const Vector3& v) const;
        GLfloat length(void) const;//return length of vector
        GLfloat lengthSquared(void) const;
        void normalize(void);//changes values so that the length of the vector is 1
        GLfloat dot(const Vector3& v) const;//skalarprodukt
        Vector3 cross(const Vector3& v) const;//kreuzprodukt
        
        
        
        static const Vector3 Zero;
        static const Vector3 X_Axis;
        static const Vector3 Y_Axis;
        static const Vector3 Z_Axis;
};

