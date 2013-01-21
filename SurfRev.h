#ifndef _SURFREV_H_
#define _SURFREV_H_

#include <Fl/gl.h>
#include <gl/glu.h>
#include "libtarga.h"
#include "ProjUtils.h"
#include "Mesh.h"
#include <list>
#include <vector>

class SurfRev {
public:
	// Constructor
	SurfRev(float (*f)(float x, float m, float h), float (*ypath)(float x, float m, float h), float m, float h, int numA, int numX);
	SurfRev(const std::list<Point2f>& listPoints, float (*ypath)(float x, float m, float h), float m, float h);

	// Destructor
	~SurfRev(void);

private:
	
	bool m_bFuncMode;
	float height;
	float slope;
	int m_numA;
	int m_numX;
	float (*m_f)(float x, float m, float h); // The function to rotate about z axis.
	float (*m_fypath)(float x, float m, float h); // The function to skew along x-axis
	std::list<Point2f> m_listPoints;
	//GLubyte m_dlSurfRev; // The display list for revolved surface.
	
public:
	Mesh* m_pMesh;
	Mesh* Subdivide(bool bRefine);
	void Draw();
	bool Initialize();
};

#endif // _SURFREV_H_ 