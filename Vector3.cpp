/*
* Modifications by Steve Coward
* Portland State University CS547
* steve-coward@comcast.net
*/

#include "Vector3.h"
#include "ProjUtils.h"
#include <stdio.h>
#include <FL/math.h>
#include <stdlib.h>
#include <iostream>
#include <assert.h>

Vector3::Vector3(void)
{
	vec[0] = 0;
	vec[1] = 0;
	vec[2] = 0;
};
Vector3::Vector3(GLfloat x, GLfloat y, GLfloat z)
{
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
}
Vector3::Vector3(const GLfloat *v)
{
	vec[0] = v[0];
	vec[1] = v[1];
	vec[2] = v[2];
}
Vector3::Vector3(const Vector3 &v)
{
	vec[0] = v[0];
	vec[1] = v[1];
	vec[2] = v[2];
}

GLfloat* Vector3::getGLfloat3v()
{
	return(vec);
}
GLfloat* Vector3::getGLfloat2v()
{
	return(vec);
}

Vector3& Vector3::operator= (const Vector3& v)
{
	if (this == &v) {
		return(*this);
	}

	vec[0] = v[0];
	vec[1] = v[1];
	vec[2] = v[2];

	return(*this);
}
// issue use operator overide
Vector3& Vector3::set(GLfloat x, GLfloat y, GLfloat z)
{
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
	return(*this);
}
Vector3& Vector3::set(GLfloat* v)
{
	vec[0] = v[0];
	vec[1] = v[1];
	vec[2] = v[2];
	return(*this);
}

GLfloat& Vector3::operator[](int i)
{
	assert(i<3);

	return(vec[i]);
}
GLfloat Vector3::operator[](int i) const
{
	assert(i<3);

	return(vec[i]);
}
Vector3& Vector3::operator+=(const Vector3& v)
{
	*this = *this + v;

	return(*this);
}
Vector3& Vector3::operator-=(const Vector3& v)
{
	*this = *this - v;

	return(*this);
}
Vector3& Vector3::operator*=(GLfloat s)
{
	*this = *this * s;

	return(*this);
}
Vector3& Vector3::operator/=(GLfloat s)
{
	*this = *this / s;

	return(*this);
}
Vector3 Vector3::operator+(const Vector3& v) const
{
	Vector3 sum;

	sum[0] = vec[0] + v[0];
	sum[1] = vec[1] + v[1];
	sum[2] = vec[2] + v[2];

	return(sum);
}
Vector3 Vector3::operator-(const Vector3& v) const
{
	Vector3 diff;

	diff[0] = vec[0] - v[0];
	diff[1] = vec[1] - v[1];
	diff[2] = vec[2] - v[2];

	return(diff);
}
Vector3 Vector3::operator*(GLfloat s) const
{
	Vector3 prod;

	prod[0] = vec[0] * s;
	prod[1] = vec[1] * s;
	prod[2] = vec[2] * s;

	return(prod);
}
Vector3 Vector3::operator/(GLfloat s) const
{
	Vector3 prod;

	assert(s!=0);

	if (s != 0) {
		prod[0] = vec[0] / s;
		prod[1] = vec[1] / s;
		prod[2] = vec[2] / s;
	}
	else {
		return(*this);
	}

	return(prod);
}
Vector3 Vector3::operator-(void)
{
	return(*this * -1.0f);
}
bool Vector3::operator==(const Vector3& v) const
{
	return((vec[0]==v[0]) && (vec[1]==v[1]) && (vec[2]==v[2]));
}
bool Vector3::operator!=(const Vector3& v) const
{
	return((vec[0]!=v[0]) || (vec[1]!=v[1]) || (vec[2]!=v[2]));
}

GLfloat Vector3::length(void) const
{
	return( sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2] ) );
}
GLfloat Vector3::lengthSquared(void) const
{
	return( vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2] );
}
void Vector3::normalize(void)
{
	double  l = sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);

	if ( l == 0.0 ) {
		return;
	}

	vec[0] /= (float)l;
	vec[1] /= (float)l;
	vec[2] /= (float)l;
}
Vector3 Vector3::scale(float len)
{
	Vector3 s;

	s = vec;
	s.normalize();
	s[0] *= len;
	s[1] *= len;
	s[2] *= len;

	return(s);
}
GLfloat Vector3::dot(const Vector3& v) const
{
	return(vec[0] * v[0] + vec[1] * v[1] + vec[2] * v[2]);
}
Vector3 Vector3::cross(const Vector3& v) const
{
	Vector3 xprod;

	xprod[0] = vec[1]*v[2] - vec[2]*v[1];
	xprod[1] = vec[2]*v[0] - vec[0]*v[2];
	xprod[2] = vec[0]*v[1] - vec[1]*v[0];

	return(xprod);
}
Vector3 Vector3::midPt(const Vector3& v) const
{
	Vector3 mid;

	mid[0] = (vec[0] + v[0])/2;
	mid[1] = (vec[1] + v[1])/2;
	mid[2] = (vec[2] + v[2])/2;

	return(mid);
}
GLfloat Vector3::distance(const Vector3& v) const
{
	return( sqrt((vec[0]-v[0])*(vec[0]-v[0]) + (vec[1]-v[1])*(vec[1]-v[1]) + (vec[2]-v[2])*(vec[2]-v[2]) ) );
}
GLfloat Vector3::distanceSquared(const Vector3& v) const
{
	return( (vec[0]-v[0])*(vec[0]-v[0]) + (vec[1]-v[1])*(vec[1]-v[1]) + (vec[2]-v[2])*(vec[2]-v[2]) );
}
