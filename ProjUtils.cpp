
#include <stdio.h>
#include "ProjUtils.h"
#include <FL/math.h>
#include <stdlib.h>
#include <iostream>
#include <Fl/gl.h>
#include <GL/glu.h>
#include <fl/glut.h>
#include <assert.h>
#include <limits>

int stackdepth = 1;
int liststackdepth = 1;

void Push(bool check)
{
	int depth;
	GLenum glError;

	if (check) {
		if (liststackdepth != 1) {
			std::cout << "Push stack check mismatch" << "\n";
		}
		glGetIntegerv (GL_MODELVIEW_STACK_DEPTH, &depth);
		glPushMatrix();
		glError = GetError(__LINE__, __FILE__);
		glGetIntegerv (GL_MODELVIEW_STACK_DEPTH, &depth);
		stackdepth++;
		std::cout << "Push" << stackdepth << " " << depth << "\n";
		if (depth != stackdepth) {
			std::cout << "Push stack mismatch" << "\n";
			//assert(depth == stackdepth);
		}
	}
	else {
		// calling within display list generation??
		if (stackdepth != 1) {
			std::cout << "Push stackx check mismatch" << "\n";
		}
		glPushMatrix();
		liststackdepth++;
	}
}
void Pop(bool check)
{
	int depth;
	GLenum glError;

	if (check) {
		if (liststackdepth != 1) {
			std::cout << "Pop stack check mismatch" << "\n";
		}
		glGetIntegerv (GL_MODELVIEW_STACK_DEPTH, &depth);
		glPopMatrix();
		glError = GetError(__LINE__, __FILE__);
		glGetIntegerv (GL_MODELVIEW_STACK_DEPTH, &depth);
		stackdepth--;
		std::cout << "Pop" << stackdepth << " " << depth << "\n";
		if (depth != stackdepth) {
			std::cout << "Pop stack mismatch" << "\n";
			//assert(depth == stackdepth);
		}
	}
	else {
		// calling within display list generation??
		if (stackdepth != 1) {
			std::cout << "Pop stackx check mismatch" << "\n";
		}
		glPopMatrix();
		liststackdepth--;
	}
}
void GetDepth()
{
	int depth;
	glGetIntegerv (GL_MODELVIEW_STACK_DEPTH, &depth);
	std::cout << "GetDepth" << stackdepth << " " << depth << "\n";
	if (depth != stackdepth) {
		std::cout << "GetDepth stack mismatch" << "\n";
		//assert(depth == stackdepth);
	}

	return;
}

// Normalize a 3d vector.
void Normalize_3(float v[3])
{
    double  l = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

    if ( l == 0.0 )
	return;

    v[0] /= (float)l;
    v[1] /= (float)l;
    v[2] /= (float)l;
}

// Make a 3d vector
void v (float* vo, float x, float y, float z)
{
	vo[0] = x;
	vo[1] = y;
	vo[2] = z;
}
// Make a 3d vector
void v (float* vo, float* vi)
{
	vo[0] = vi[0];
	vo[1] = vi[1];
	vo[2] = vi[2];
}

// Compute the cross product a X b into pOut
void VectorGetNormal (float va[3], float vb[3], float vout[3])
{
   vout[0] = va[1] * vb[2] - va[2] * vb[1];
   vout[1] = va[2] * vb[0] - va[0] * vb[2];
   vout[2] = va[0] * vb[1] - va[1] * vb[0];
}
// vb is common point (tail intersection point) of va and vc
void VectorGetNormal (float va[3], float vb[3], float vc[3], float vout[3])
{
   vout[0] = (va[1]-vb[1]) * (vc[2]-vb[2]) - (va[2]-vb[2]) * (vc[1]-vb[1]);
   vout[1] = (va[2]-vb[2]) * (vc[0]-vb[0]) - (va[0]-vb[0]) * (vc[2]-vb[2]);
   vout[2] = (va[0]-vb[0]) * (vc[1]-vb[1]) - (va[1]-vb[1]) * (vc[0]-vb[0]);
   Normalize_3(vout);
}

void ClearError ()
{
	GLenum glError;

	do {
		glError = glGetError();
	} while (glError != GL_NO_ERROR);
}

GLenum GetError (int lineNum, std::string file)
{
	GLenum glError;
	
	glError = glGetError();
	switch (glError) {
		case GL_NO_ERROR:
			//std::cout << "No GL errors detected at this time" << std::endl; 
			return(glError);
		case GL_INVALID_ENUM:
			std::cout << "Invalid Enum GL error" << std::endl;
			break;
		case GL_INVALID_VALUE:
			std::cout << "Invalid Value GL error" << std::endl;
			break;
		case GL_INVALID_OPERATION:
			std::cout << "Invalid Operation GL error" << std::endl;
			break;
		case GL_STACK_OVERFLOW:
			std::cout << "Stack Overflow GL error" << std::endl;
			break;
		case GL_STACK_UNDERFLOW:
			std::cout << "Stack Underflow GL error" << std::endl;
			break;
		case GL_OUT_OF_MEMORY:
			std::cout << "Out of memory GL error" << std::endl;
		default:
			std::cout << "Undefined GL error detected: " << glError << std::endl;
			break;
	}
	std::cout << "line:" << lineNum << " file:" << file.c_str() << std::endl;

	return(glError);
}

float Curve2DZero(float x,  float d, float h)
{
	return(0);
	//return(0.1f*(x-10.0f)*(x-10.0f));
}
float Curve2DIdentity(float x,  float d, float h)
{
	return(x);
	//return(0.1f*(x-10.0f)*(x-10.0f));
}
float Curve2DConstant(float x,  float d, float h)
{
	return(d);
	//return(0.1f*(x-10.0f)*(x-10.0f));
}
float Curve2DLinear(float x,  float xi, float yi)
{
	return(yi-x*yi/xi);
	//return(0.1f*(x-10.0f)*(x-10.0f));
}
float Curve2DQuadratic(float x, float b, float h)
{
	return((x-b)*(x-b)*h/(b*b));
}
float Curve2DQuadraticP(float x, float b, float h)
{
	return(2.0f*(x-b)*h/(b*b));
}
float Curve2DArc(float x, float r, float xi)
{
	return(sqrt((r*r - (x-xi)*(x-xi))));
}
float Curve2DArcP(float x, float r, float xi)
{
	if ((x-xi) == r) {
		return(-std::numeric_limits<float>::infinity());
	}
	else if ((x-xi) == -r) {
		return(std::numeric_limits<float>::infinity());
	}
	else {
		return((x-xi)/sqrt((r*r - (x-xi)*(x-xi))));
	}
}
void ShroomOutline(std::list<Point2f>* listPoints)
{
	Point2f p;

	p.x = 0.0f;
	p.y = 15.0f;
	listPoints->push_back(p);
	p.x = 4.0f;
	p.y = 14.0f;
	listPoints->push_back(p);
	p.x = 6.0f;
	p.y = 14.33f;
	listPoints->push_back(p);
	p.x = 7.0f;
	p.y = 14.0f;
	listPoints->push_back(p);
	p.x = 8.67f;
	p.y = 13.0f;
	listPoints->push_back(p);
	p.x = 9.33f;
	p.y = 12.0f;
	listPoints->push_back(p);
	p.x = 9.67f;
	p.y = 11.0f;
	listPoints->push_back(p);
	p.x = 9.0f;
	p.y = 10.0f;
	listPoints->push_back(p);
	p.x = 8.0f;
	p.y = 9.0f;
	listPoints->push_back(p);
	p.x = 6.0f;
	p.y = 12.0f;
	listPoints->push_back(p);
	p.x = 3.0f;
	p.y = 11.0f;
	listPoints->push_back(p);
	p.x = 1.0f;
	p.y = 11.0f;
	listPoints->push_back(p);
	p.x = 1.25f;
	p.y = 5.5f;
	listPoints->push_back(p);
	p.x = 1.5f;
	p.y = 0.0f;
	listPoints->push_back(p);

	/*m_f = f;
	p.x = 0.0f;
	p.y = 5.0f;
	listPoints->push_back(p);
	p.x = 5.0f;
	p.y = 5.0f;
	listPoints->push_back(p);
	p.x = 8.0f;
	p.y = 8.0f;
	listPoints->push_back(p);
	p.x = 10.0f;
	p.y = 8.0f;
	listPoints->push_back(p);
	p.x = 10.0f;
	p.y = 0.0f;
	listPoints->push_back(p);*/

	//p.x = 0.0f;
	//p.y = 20.0f;
	//listPoints->push_back(p);
	//p.x = 0.4f;
	//p.y = 20.0f;
	//listPoints->push_back(p);
	//p.x = 0.8f;
	//p.y = 20.0f;
	//listPoints->push_back(p);
	//p.x = 1.2f;
	//p.y = 20.0f;
	//listPoints->push_back(p);
	//p.x = 1.6f;
	//p.y = 20.0f;
	//listPoints->push_back(p);
	//p.x = 2.0f;
	//p.y = 20.0f;
	//listPoints->push_back(p);
	//p.x = 2.0f;
	//p.y = 18.0f;
	//listPoints->push_back(p);
	//p.x = 2.0f;
	//p.y = 16.0f;
	//listPoints->push_back(p);
	//p.x = 2.0f;
	//p.y = 14.0f;
	//listPoints->push_back(p);
	//p.x = 2.0f;
	//p.y = 10.0f;
	//listPoints->push_back(p);
	//p.x = 2.0f;
	//p.y = 5.0f;
	//listPoints->push_back(p);
	//p.x = 2.0f;
	//p.y = 0.0f;
	//listPoints->push_back(p);
	
	/*p.x = 0.0f;
	p.y = 10.0f;
	listPoints->push_back(p);
	p.x = 1.0f;
	p.y = 9.0f;
	listPoints->push_back(p);
	p.x = 2.0f;
	p.y = 8.0f;
	listPoints->push_back(p);
	p.x = 3.0f;
	p.y = 7.0f;
	listPoints->push_back(p);
	p.x = 4.0f;
	p.y = 6.0f;
	listPoints->push_back(p);
	p.x = 5.0f;
	p.y = 5.0f;
	listPoints->push_back(p);
	p.x = 6.0f;
	p.y = 4.0f;
	listPoints->push_back(p);
	p.x = 7.0f;
	p.y = 3.0f;
	listPoints->push_back(p);
	p.x = 8.0f;
	p.y = 2.0f;
	listPoints->push_back(p);
	p.x = 9.0f;
	p.y = 1.0f;
	listPoints->push_back(p);
	p.x = 0.0f;
	p.y = 10.0f;
	listPoints->push_back(p);*/
}
