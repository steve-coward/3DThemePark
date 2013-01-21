/*
* Modifications by Steve Coward
* Portland State University CS547
* steve-coward@comcast.net
*/

#include "PolySweep.h"
#include "ProjUtils.h"
#include "Mesh.h"
#include <stdio.h>
#include <FL/math.h>
#include <stdlib.h>
#include <iostream>
#include "Vector3.h"

PolySweep::PolySweep(float (*y)(float x, float m, float h), float (*yp)(float x, float m, float h), float arg1, float arg2, int numA, int numX, float pathStart, float pathEnd, bool bEndCap, bool bUseTexCoors)
{
	m_pMesh = NULL;
	m_bFuncMode = true;
	m_fy = y;
	m_fyp = yp;
	m_arg1 = arg1;
	m_arg2 = arg2;
	m_numA = numA;
	m_numX = numX;
	m_pathStart = pathStart;
	m_pathEnd = pathEnd;
	m_bUseTexCoors = bUseTexCoors;
}

bool PolySweep::Initialize()
{
	m_pMesh = new Mesh();
	if (!m_pMesh) {
		return(false);
	}

	m_pMesh->bUseTexCoors = m_bUseTexCoors;
	
	if (m_bFuncMode) {
		int loopstartvertexindex;
		float TwoPi=2*4*atan(1.0f);
		float x;
		float v0[3], v1[3], v2[3], v3[3], v4[3], v5[3], v6[3], v7[3];
		Vector3 veca, vecb, vecc;
		int numVerts = 0;
		int vi3[3];
		int vt3[3];

		loopstartvertexindex = 0;
		float a = 1.0f;
		float dx = (m_pathEnd - m_pathStart)/m_numA;
		float m;
		float theta;
		// assume square of side length a as sweep polygon
		// assume sweep path passes through lower left corner of sweep poly
		// assume poly face orthogonal to start of sweep path
		// sweep path defined by y = f(x).
		// assume sweep path is smooth curve.
		// Currently adding 8 vertices per loop iteration
		if (m_bUseTexCoors) {
			m_pMesh->AddTexCoor(Vector3(0.0f, 0.0f, 0.0f));
			m_pMesh->AddTexCoor(Vector3(0.5f, 0.0f, 0.0f));
			m_pMesh->AddTexCoor(Vector3(0.0f, 0.5f, 0.0f));
			m_pMesh->AddTexCoor(Vector3(0.5f, 0.5f, 0.0f));
		}
		
		if (m_bEndCap) {
			// draw the first cap
			m = m_fyp(m_pathStart, m_arg1, m_arg2);
			theta = atan(m); // in rads
			v(v0, m_pathStart-a*sin(theta), m_fy(m_pathStart, m_arg1, m_arg2)+a*cos(theta), 0.0f);
			v(v1, m_pathStart, m_fy(m_pathStart, m_arg1, m_arg2),   0.0f);
			v(v2, m_pathStart-a*sin(theta), m_fy(m_pathStart, m_arg1, m_arg2)+a*cos(theta),    a);
			v(v3, m_pathStart, m_fy(m_pathStart, m_arg1, m_arg2),      a);

			m_pMesh->AddVertex(veca.set(v0));
			m_pMesh->AddVertex(veca.set(v1));			
			m_pMesh->AddVertex(veca.set(v2));			
			m_pMesh->AddVertex(veca.set(v3));			

			vi3[0] = loopstartvertexindex + 1;
			vi3[1] = loopstartvertexindex + 2;
			vi3[2] = loopstartvertexindex + 0;
			vt3[0] = 0;
			vt3[1] = 3;
			vt3[2] = 2;

			m_pMesh->AddFace(3, vi3, vt3);

			vi3[0] = loopstartvertexindex + 1;
			vi3[1] = loopstartvertexindex + 3;
			vi3[2] = loopstartvertexindex + 2;
			vt3[0] = 0;
			vt3[1] = 1;
			vt3[2] = 3;
			m_pMesh->AddFace(3, vi3, vt3);

			loopstartvertexindex += 4;
		}
		
		for (x = m_pathStart; x <m_pathEnd;x += dx) {
			//glBegin(GL_POLYGON);
			// 0 (x,f(x)+a,0)   2 (x,f(x)+a,a)
			// 1 (x,f(x)+0,0)   3 (x,f(x)+0,a)
			//
			// 0-5-1 bottom face
			// 4-5-0
			// 2-4-0 side face
			// 6-4-2
			// 3-6-2 top face
			// 7-6-3
			// 1-7-3 side face
			// 5-7-1
			m = m_fyp(x, m_arg1, m_arg2);
			theta = atan(m); // in rads
			v(v0, x-a*sin(theta), m_fy(x, m_arg1, m_arg2)+a*cos(theta), 0.0f);
			v(v1, x, m_fy(x, m_arg1, m_arg2),   0.0f);
			v(v2, x-a*sin(theta), m_fy(x, m_arg1, m_arg2)+a*cos(theta),    a);
			v(v3, x, m_fy(x, m_arg1, m_arg2),      a);

			m = m_fyp(x+dx, m_arg1, m_arg2);
			theta = atan(m); // in rads
			v(v4, x+dx-a*sin(theta), m_fy(x+dx, m_arg1, m_arg2)+a*cos(theta), 0.0f);
			v(v5, x+dx, m_fy(x+dx, m_arg1, m_arg2),   0.0f);
			v(v6, x+dx-a*sin(theta), m_fy(x+dx, m_arg1, m_arg2)+a*cos(theta),    a);
			v(v7, x+dx, m_fy(x+dx, m_arg1, m_arg2),      a);

			m_pMesh->AddVertex(veca.set(v0));			
			m_pMesh->AddVertex(veca.set(v1));			
			m_pMesh->AddVertex(veca.set(v2));			
			m_pMesh->AddVertex(veca.set(v3));			
			m_pMesh->AddVertex(veca.set(v4));			
			m_pMesh->AddVertex(veca.set(v5));			
			m_pMesh->AddVertex(veca.set(v6));			
			m_pMesh->AddVertex(veca.set(v7));			

			// 0-5-1 bottom face
			vi3[0] = loopstartvertexindex + 0;
			vi3[1] = loopstartvertexindex + 5;
			vi3[2] = loopstartvertexindex + 1;
			vt3[0] = 0;
			vt3[1] = 3;
			vt3[2] = 1;
			m_pMesh->AddFace(3, vi3, vt3);

			// 4-5-0
			vi3[0] = loopstartvertexindex + 4;
			vi3[1] = loopstartvertexindex + 5;
			vi3[2] = loopstartvertexindex + 0;
			vt3[0] = 2;
			vt3[1] = 3;
			vt3[2] = 0;
			m_pMesh->AddFace(3, vi3, vt3);

			// 2-4-0 side face
			vi3[0] = loopstartvertexindex + 2;
			vi3[1] = loopstartvertexindex + 4;
			vi3[2] = loopstartvertexindex + 0;
			vt3[0] = 0;
			vt3[1] = 3;
			vt3[2] = 1;
			m_pMesh->AddFace(3, vi3, vt3);

			// 6-4-2
			vi3[0] = loopstartvertexindex + 6;
			vi3[1] = loopstartvertexindex + 4;
			vi3[2] = loopstartvertexindex + 2;
			vt3[0] = 2;
			vt3[1] = 3;
			vt3[2] = 0;
			m_pMesh->AddFace(3, vi3, vt3);

			// 3-6-2 top face
			vi3[0] = loopstartvertexindex + 3;
			vi3[1] = loopstartvertexindex + 6;
			vi3[2] = loopstartvertexindex + 2;
			vt3[0] = 0;
			vt3[1] = 3;
			vt3[2] = 1;
			m_pMesh->AddFace(3, vi3, vt3);

			// 7-6-3
			vi3[0] = loopstartvertexindex + 7;
			vi3[1] = loopstartvertexindex + 6;
			vi3[2] = loopstartvertexindex + 3;
			vt3[0] = 2;
			vt3[1] = 3;
			vt3[2] = 0;
			m_pMesh->AddFace(3, vi3, vt3);

			// 1-7-3 side face
			vi3[0] = loopstartvertexindex + 1;
			vi3[1] = loopstartvertexindex + 7;
			vi3[2] = loopstartvertexindex + 3;
			vt3[0] = 0;
			vt3[1] = 3;
			vt3[2] = 1;
			m_pMesh->AddFace(3, vi3, vt3);

			// 5-7-1
			vi3[0] = loopstartvertexindex + 5;
			vi3[1] = loopstartvertexindex + 7;
			vi3[2] = loopstartvertexindex + 1;
			vt3[0] = 2;
			vt3[1] = 3;
			vt3[2] = 0;
			m_pMesh->AddFace(3, vi3, vt3);

			loopstartvertexindex += 8;
			//break;

			//glEnd();
		}

		if (m_bEndCap) {
			// draw the last cap
			m = m_fyp(m_pathEnd, m_arg1, m_arg2);
			theta = atan(m); // in rads
			v(v0, m_pathEnd-a*sin(theta), m_fy(m_pathEnd, m_arg1, m_arg2)+a*cos(theta), 0.0f);
			v(v1, m_pathEnd, m_fy(m_pathEnd, m_arg1, m_arg2),   0.0f);
			v(v2, m_pathEnd-a*sin(theta), m_fy(m_pathEnd, m_arg1, m_arg2)+a*cos(theta),    a);
			v(v3, m_pathEnd, m_fy(m_pathEnd, m_arg1, m_arg2),      a);

			m_pMesh->AddVertex(veca.set(v0));			
			m_pMesh->AddVertex(veca.set(v1));			
			m_pMesh->AddVertex(veca.set(v2));			
			m_pMesh->AddVertex(veca.set(v3));			

			vi3[0] = loopstartvertexindex + 0;
			vi3[1] = loopstartvertexindex + 2;
			vi3[2] = loopstartvertexindex + 1;
			vt3[0] = 2;
			vt3[1] = 3;
			vt3[2] = 0;
			m_pMesh->AddFace(3, vi3, vt3);

			vi3[0] = loopstartvertexindex + 2;
			vi3[1] = loopstartvertexindex + 3;
			vi3[2] = loopstartvertexindex + 1;
			vt3[0] = 3;
			vt3[1] = 1;
			vt3[2] = 0;
			m_pMesh->AddFace(3, vi3, vt3);
		}

		m_pMesh->CalcNormals();

		//m_pMesh->Dump();
	}

	m_pMesh->Initialize();

	return(true);
}


PolySweep::~PolySweep()
{
	if (m_pMesh != NULL) {
		delete m_pMesh;
		m_pMesh = NULL;
	}
}

void PolySweep::Draw()
{
	m_pMesh->draw();
}

Mesh* PolySweep::Subdivide(bool bRefine)
{
	Mesh* newMesh;
	std::vector<Face>::iterator fitr;
	std::vector<VertexID>::iterator vitr;
	int vi;
	int Vi[3];

	int i = 0;
	newMesh = new Mesh();
	if (bRefine) {
		fitr = m_pMesh->vecFaces.begin();
		while (fitr != m_pMesh->vecFaces.end()) {
			//if (i&1) {
				vitr = fitr->vecVert.begin();
				vi = newMesh->numVerts;
				while (vitr != fitr->vecVert.end()) {
					newMesh->AddVertex(m_pMesh->vecPts[vitr->vertIndex]);
					++vitr;
				}
				newMesh->AddVertex(newMesh->vecPts[vi+0].midPt(newMesh->vecPts[vi+1]).scale(slope));
				newMesh->AddVertex(newMesh->vecPts[vi+0].midPt(newMesh->vecPts[vi+2]).scale(slope));
				newMesh->AddVertex(newMesh->vecPts[vi+1].midPt(newMesh->vecPts[vi+2]).scale(slope));

				Vi[0] = vi+0; Vi[1] = vi+3; Vi[2] = vi+4; newMesh->AddFace(3, Vi);
				Vi[0] = vi+3; Vi[1] = vi+1; Vi[2] = vi+5; newMesh->AddFace(3, Vi);
				Vi[0] = vi+3; Vi[1] = vi+5; Vi[2] = vi+4; newMesh->AddFace(3, Vi);
				Vi[0] = vi+4; Vi[1] = vi+5; Vi[2] = vi+2; newMesh->AddFace(3, Vi);
			//}

			++fitr;
			i++;
		}
	}

	newMesh->CalcNormals();

	return(newMesh);
}

