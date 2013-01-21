/*
* Modifications by Steve Coward
* Portland State University CS547
* steve-coward@comcast.net
*/

#include "SurfRev.h"
#include "ProjUtils.h"
#include "Mesh.h"
#include <stdio.h>
#include <FL/math.h>
#include <stdlib.h>
#include <iostream>
#include "Vector3.h"

SurfRev::SurfRev(float (*f)(float x, float m, float h), float (*ypath)(float x, float m, float h), float m, float h, int numA, int numX)
{
	m_pMesh = NULL;
	m_bFuncMode = true;
	m_f = f;
	m_fypath = ypath;
	height = h;
	slope = m;
	m_numA = numA;
	m_numX = numX;
}
SurfRev::SurfRev(const std::list<Point2f>& listPoints, float (*ypath)(float x, float m, float h), float m, float h)
{
	m_pMesh = NULL;
	m_bFuncMode = false;
	m_f = NULL;
	m_fypath = ypath;
	height = h;
	slope = m;

	std::list<Point2f>::const_iterator itr;
	itr = listPoints.begin();
	while (itr != listPoints.end()) {
		m_listPoints.push_back(*itr);
		++itr;
	}
}

bool SurfRev::Initialize()
{
	m_pMesh = new Mesh();
	if (!m_pMesh) {
		return(false);
	}

	if (m_bFuncMode) {
		float TwoPi=2*4*atan(1.0f);
		float deltaPhi = TwoPi/(float)m_numA;
		float deltaX = slope/(float)m_numX;
		float x;
		float phi;
		float vNormal[3];
		float va[3];
		float vb[3];
		float vc[3];
		Vector3 veca, vecb, vecc;
		int numVerts = 0;
		int v3[3];

		GLUquadricObj *quadratic;
		quadratic=gluNewQuadric(); // Create A Pointer To The Quadric Object ( NEW )
		
		//m_dlSurfRev = glGenLists(1);
		//glNewList(m_dlSurfRev, GL_COMPILE);
		glDisable(GL_TEXTURE_2D);
		//glColor3f(0.0, 0.0, 1.0);

		for (phi=0; phi < TwoPi; phi+=deltaPhi) {
			//glBegin(GL_POLYGON);

			v(vc, m_fypath(m_f(0.0, slope, height ), slope, height ), 0.0f, m_f(0.0f, slope, height ));
			//glNormal3f(m_fypath(0.0f, slope, height ), 0.0f, 1.0f);
			//glVertex3fv(vc);

			v(va, deltaX*cos(phi)+m_fypath(m_f(deltaX, slope, height ), slope, height ), deltaX*sin(phi), m_f(deltaX, slope, height ));
			v(vb, deltaX*cos(phi+deltaPhi)+m_fypath(m_f(deltaX, slope, height ), slope, height ), deltaX*sin(phi+deltaPhi), m_f(deltaX, slope, height ));
			VectorGetNormal(vc, vb, va, vNormal);
			//glNormal3fv(vNormal);
			//glVertex3fv(va);

			for (x=deltaX; x<slope; x+=deltaX) {
				v(vb, x*cos(phi+deltaPhi)+m_fypath(m_f(x, slope, height ), slope, height ), x*sin(phi+deltaPhi), m_f(x, slope, height ));
				VectorGetNormal(vc, vb, va, vNormal);
				//glNormal3fv(vNormal);
				//glVertex3fv(vb);
				v3[0] = m_pMesh->AddVertex(veca.set(vc));
				v3[1] = m_pMesh->AddVertex(vecb.set(va));
				v3[2] = m_pMesh->AddVertex(vecc.set(vb));
				m_pMesh->AddFace(3, v3);

				v(vc, vb);

				v(vb, (x+deltaX)*cos(phi)+m_fypath(m_f(x+deltaX, slope, height ), slope, height ), (x+deltaX)*sin(phi), m_f(x+deltaX, slope, height ));
				VectorGetNormal(vc, vb, va, vNormal);
				//glNormal3fv(vNormal);
				//glVertex3fv(vb);
				v3[0] = m_pMesh->AddVertex(veca.set(vc));
				v3[1] = m_pMesh->AddVertex(vecb.set(va));
				v3[2] = m_pMesh->AddVertex(vecc.set(vb));
				m_pMesh->AddFace(3, v3);

				v(va, vb);
			}

			v(vb, x*cos(phi+deltaPhi)+m_fypath(m_f(x, slope, height ), slope, height ), x*sin(phi+deltaPhi), m_f(x, slope, height ));
			VectorGetNormal(vc, vb, va, vNormal);
			//glNormal3fv(vNormal);
			//glVertex3fv(vb);
			v3[0] = m_pMesh->AddVertex(veca.set(vc));
			v3[1] = m_pMesh->AddVertex(vecb.set(va));
			v3[2] = m_pMesh->AddVertex(vecc.set(vb));
			m_pMesh->AddFace(3, v3);

			//glEnd();
		}

		gluQuadricOrientation(quadratic,GLU_INSIDE);
		//draw the first cap
		gluDisk( quadratic, 0.0, slope, 16, 1);

		//glEndList();
		m_pMesh->CalcNormals();

		//m_pMesh->Dump();
	}
	else {
		float TwoPi=2*4*atan(1.0f);
		float deltaPhi = TwoPi/72.0f;
		int numXs;
		float phi;
		float vNormal[3];
		float va[3];
		float vb[3];
		float vc[3];
		Point2f p2f;
		std::list<Point2f>::iterator itr;

		//m_dlSurfRev = glGenLists(1);
		//glNewList(m_dlSurfRev, GL_COMPILE);
		glDisable(GL_TEXTURE_2D);
		//glColor3f(0.0, 0.0, 1.0);
		glShadeModel(GL_SMOOTH);

		// increasing phi is counter clockwise
		for (phi=0; phi < TwoPi; phi+=deltaPhi) {
			numXs = (int)m_listPoints.size();
			glBegin(GL_TRIANGLE_STRIP);
			itr = m_listPoints.begin();
			numXs--;
			p2f = *itr;

			v(vc, m_fypath(p2f.y, slope, height ), 0.0f, p2f.y);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glVertex3fv(vc);

			++itr;
			numXs--;
			p2f = *itr;
			v(va, p2f.x*cos(phi)+m_fypath(p2f.y, slope, height ), p2f.x*sin(phi), p2f.y);
			v(vb, p2f.x*cos(phi+deltaPhi)+m_fypath(p2f.y, slope, height ), p2f.x*sin(phi+deltaPhi), p2f.y);
			VectorGetNormal(vc, vb, va, vNormal);
			glNormal3fv(vNormal);
			//glColor3f(0.0, 0.0, 1.0);
			glVertex3fv(va);

			while (numXs > 0) {
				p2f = *itr;
				v(vb, p2f.x*cos(phi+deltaPhi)+m_fypath(p2f.y, slope, height ), p2f.x*sin(phi+deltaPhi), p2f.y);
				VectorGetNormal(vc, vb, va, vNormal);
				glNormal3fv(vNormal);
				//glColor3f(1.0, 0.0, 0.0);
				glVertex3fv(vb);

				v(vc, vb);

				++itr;
				p2f = *itr;
				v(vb, p2f.x*cos(phi)+m_fypath(p2f.y, slope, height ), p2f.x*sin(phi),p2f.y);
				VectorGetNormal(vc, vb, va, vNormal);
				glNormal3fv(vNormal);
				//glColor3f(0.0, 0.0, 1.0);
				glVertex3fv(vb);

				v(va, vb);

				numXs--;
			}

			p2f = *itr;
			v(vb, p2f.x*cos(phi+deltaPhi)+m_fypath(p2f.y, slope, height ), p2f.x*sin(phi+deltaPhi), p2f.y);
			VectorGetNormal(vc, vb, va, vNormal);
			glNormal3fv(vNormal);
			glVertex3fv(vb);

			glEnd();
			//break;
		}

		glEndList();
	}

	m_pMesh->Initialize();

	return(true);
}


SurfRev::~SurfRev()
{
	if (m_pMesh != NULL) {
		delete m_pMesh;
		m_pMesh = NULL;
	}
}

void SurfRev::Draw()
{
	m_pMesh->draw();
}

Mesh* SurfRev::Subdivide(bool bRefine)
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

