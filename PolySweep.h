#ifndef _POLYSWEEP_H_
#define _POLYSWEEP_H_

#include <Fl/gl.h>
#include <gl/glu.h>
#include "libtarga.h"
#include "ProjUtils.h"
#include "Mesh.h"
#include <list>
#include <vector>

class PolySweep {
public:
	// Constructor
	PolySweep(float (*y)(float x, float m, float h), float (*yp)(float x, float m, float h), float arg1, float arg2, int numA, int numX, float pathStart, float pathEnd, bool bEndCap, bool bUseTexCoor);
	PolySweep(const std::list<Point2f>& listPoints, float (*ypath)(float x, float m, float h), float m, float h);

	// Destructor
	~PolySweep(void);

private:
	bool m_bFuncMode;
	float height;
	float slope;
	int m_numA;
	int m_numX;
	float m_arg1;
	float m_arg2;
	float m_pathStart;
	float m_pathEnd;
	bool m_bEndCap;
	bool m_bUseTexCoors;
	float (*m_fy)(float x, float m, float h); // The function to rotate about z axis.
	float (*m_fyp)(float x, float m, float h); // The function to skew along x-axis
	std::list<Point2f> m_listPoints;
	//GLubyte m_dlSurfRev; // The display list for revolved surface.
	
public:
	Mesh* m_pMesh;
	Mesh* Subdivide(bool bRefine);
	void Draw();
	bool Initialize();
};

#endif // _POLYSWEEP_H_ 