#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include <Fl/gl.h>
#include <gl/glu.h>
#include <fl/math.h>
#include "ProjUtils.h"
#include "libtarga.h"
#include <list>
#include <vector>
#include <iostream>

class Vector3 {
private:
	GLfloat vec[3];

public:
	Vector3(void);
	Vector3(GLfloat x, GLfloat y, GLfloat z);
	Vector3(const GLfloat *v);
	Vector3(const Vector3 &v);

	GLfloat* getGLfloat3v();
	GLfloat* getGLfloat2v();
	GLfloat getGLfloatY() { return(vec[0]); }
	GLfloat getGLfloatX() { return(vec[1]); }

	Vector3& operator= (const Vector3& v);
	Vector3& set(GLfloat x, GLfloat y, GLfloat z);
	Vector3& set(GLfloat* v);

	GLfloat& operator[](int i);
	GLfloat operator[](int i) const;

	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3& operator*=(GLfloat s);
	Vector3& operator/=(GLfloat s);
	Vector3 operator+(const Vector3& v) const;
	Vector3 operator-(const Vector3& v) const;
	Vector3 operator*(GLfloat s) const;
	Vector3 operator/(GLfloat s) const;
	Vector3 operator-(void);
	bool operator==(const Vector3& v) const;
	bool operator!=(const Vector3& v) const;

	GLfloat length(void) const;
	GLfloat lengthSquared(void) const;
	void normalize(void);
	Vector3 scale(float len);
	GLfloat dot(const Vector3& v) const;
	Vector3 cross(const Vector3& v) const;
	GLfloat distance(const Vector3& v) const;
	GLfloat distanceSquared(const Vector3& v) const;
	Vector3 midPt(const Vector3& v) const;

	static const Vector3 Zero;
	static const Vector3 X_Axis;
	static const Vector3 Y_Axis;
	static const Vector3 Z_Axis;

	friend std::ostream& operator<< (std::ostream& s, const Vector3& v);
};

#endif // _VECTOR3_H_