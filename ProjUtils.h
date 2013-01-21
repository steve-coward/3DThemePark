#ifndef _PROJUTILS_H_
#define _PROJUTILS_H_

#include <Fl/gl.h>
#include <gl/glu.h>
#include <fl/math.h>
#include "ProjUtils.h"
#include "libtarga.h"
#include <list>
#include <vector>

struct Point2f {
	float x;
	float y;
};

struct Point3f {
	float x;
	float y;
	float z;
};

const float TwoPi=2*4*atan(1.0f);

void v (float* vo, float x, float y, float z);
void v (float* vo, float* vi);
GLenum GetError (int lineNum, std::string file);
void ClearError();
void Normalize_3(float v[3]);
// Compute the cross product a X b into pOut
void VectorGetNormal (float va[3], float vb[3], float vout[3]);
void VectorGetNormal (float va[3], float vb[3], float vc[3], float vout[3]);
float Curve2DZero(float x, float d, float h);
float Curve2DIdentity(float x, float d, float h);
float Curve2DConstant(float x, float d, float h);
float Curve2DLinear(float x, float xi, float yi);
float Curve2DQuadratic(float x, float b, float h);
float Curve2DQuadraticP(float x, float b, float h);
float Curve2DArc(float x, float b, float h);
float Curve2DArcP(float x, float b, float h);
void ShroomOutline(std::list<Point2f>* listPoints);
void Push(bool check);
void Pop(bool check);
void GetDepth();

class ProjUtils {
public:
	// Constructor
	ProjUtils(){}

	// Destructor
	~ProjUtils(void){}

	
};

#endif // _PROJUTILS_H_