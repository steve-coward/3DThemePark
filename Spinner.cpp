/*
* Modifications by Steve Coward
* Portland State University CS547
* steve-coward@comcast.net
*/

#include "Spinner.h"
#include "SurfRev.h"
#include "ProjUtils.h"
#include "Mesh.h"
#include <stdio.h>
#include <FL/math.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>


Spinner::Spinner(GLfloat x, GLfloat y, GLfloat z)
{
	m_x = x;
	m_y = y;
	m_z = z;
	w = 0.0;
	speed = 0.01f; // revs per update
	m_baseradius = 10.0f;
}

// Destructor
Spinner::~Spinner(void)
{
}
void Spinner::ReInitialize()
{
	glDeleteLists(dlSpinner, 1);
	dlSpinner = glGenLists(1);
	glNewList(dlSpinner, GL_COMPILE);

	glPushMatrix();
	gluCylinder(quadratic, m_baseradius, m_baseradius, 5.0f, 12, 1);
	glTranslatef(0,0,5);
	m_pBase->Draw();
	

	glPushMatrix();
	glTranslatef(m_baseradius-2,0,0);
	glRotatef(45, 0.0, 1.0, 0.0);
	gluCylinder(quadratic, 1.0f, 1.0f, 2+m_baseradius, 8, 1);
	glTranslatef(0,0,m_baseradius+2);
	gluSphere(quadratic, 1.2f, 12, 6);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-m_baseradius+2,0,0);
	glRotatef(-45, 0.0, 1.0, 0.0);
	gluCylinder(quadratic, 1.0f, 1.0f, 2+m_baseradius, 8, 1);
	glTranslatef(0,0,m_baseradius+2);
	gluSphere(quadratic, 1.2f, 12, 6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,m_baseradius-2,0);
	glRotatef(-45, 1.0, 0.0, 0.0);
	gluCylinder(quadratic, 1.0f, 1.0f, 2+m_baseradius, 8, 1);
	glTranslatef(0,0,m_baseradius+2);
	gluSphere(quadratic, 1.2f, 12, 6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,-m_baseradius+2,0);
	glRotatef(45, 1.0, 0.0, 0.0);
	gluCylinder(quadratic, 1.0f, 1.0f, 2+m_baseradius, 8, 1);
	glTranslatef(0,0,m_baseradius+2);
	gluSphere(quadratic, 1.2f, 12, 6);
	glPopMatrix();

	glPopMatrix();
	glEndList();
}
void Spinner::Initialize()
{
	quadratic=gluNewQuadric(); // Create A Pointer To The Quadric Object ( NEW )
	m_pBase = new SurfRev(&Curve2DArc, &Curve2DZero, m_baseradius, 0.0f, 4, 1);
	m_pBase->Initialize();

	ReInitialize();
}
void Spinner::Draw()
{
	glPushMatrix();
	glTranslatef(m_x, m_y, m_z);
	glRotatef(w*360/TwoPi, 0.0, 0.0, 1.0);
	glCallList(dlSpinner);

	glTranslatef(0,0,5);

	//1----------------------------------
	glPushMatrix();
	glTranslatef(m_baseradius-2+0.707f*(m_baseradius+2),0,0.707f*(m_baseradius+2));
	glRotatef(m_zeta0*360/TwoPi, 0.0, 1.0, 0.0);
	gluCylinder(quadratic, 1.0f, 1.0f, m_baseradius, 8, 1);
	glTranslatef(0,0,m_baseradius);
	gluSphere(quadratic, 1.2f, 12, 6);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(m_baseradius-2+0.707f*(m_baseradius+2)+m_baseradius*sin(m_zeta0),0,0.707f*(m_baseradius+2)+m_baseradius*cos(m_zeta0));
	glRotatef(90, 0.0, 1.0, 0.0);
	gluCylinder(quadratic, 1.0f, 1.0f, m_baseradius/2, 8, 1);
	//draw the end cap
	glTranslatef( 0,0,m_baseradius/2 );
	gluQuadricOrientation(quadratic,GLU_OUTSIDE);
	gluDisk( quadratic, 0.0, 1.0f, 16, 1);
	glTranslatef( 0,0,-m_baseradius/2 );

	glTranslatef(-1.0f,0,m_baseradius/2-1.0f);
	glRotatef(90, 0.0, 1.0, 0.0);
	gluCylinder(quadratic, m_baseradius/4, m_baseradius/4, 0.5f, 8, 1);
	//draw the first cap
	gluQuadricOrientation(quadratic,GLU_INSIDE);
	gluDisk( quadratic, 0.0, m_baseradius/4, 16, 1);
	glTranslatef( 0,0,0.5f );
	//draw the second cap
	gluQuadricOrientation(quadratic,GLU_OUTSIDE);
	gluDisk( quadratic, 0.0, m_baseradius/4, 16, 1);
	glPopMatrix();

	//2----------------------------------
	glPushMatrix();
	glTranslatef(-m_baseradius+2-0.707f*(m_baseradius+2),0,0.707f*(m_baseradius+2));
	glRotatef(-m_zeta2*360/TwoPi, 0.0, 1.0, 0.0);
	gluCylinder(quadratic, 1.0f, 1.0f, m_baseradius, 8, 1);
	glTranslatef(0,0,m_baseradius);
	gluSphere(quadratic, 1.2f, 12, 6);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-m_baseradius+2-0.707f*(m_baseradius+2)-m_baseradius*sin(m_zeta2),0,0.707f*(m_baseradius+2)+m_baseradius*cos(m_zeta2));
	glRotatef(-90, 0.0, 1.0, 0.0);
	gluCylinder(quadratic, 1.0f, 1.0f, m_baseradius/2, 8, 1);
	//draw the end cap
	glTranslatef( 0,0,m_baseradius/2 );
	gluQuadricOrientation(quadratic,GLU_OUTSIDE);
	gluDisk( quadratic, 0.0, 1.0f, 16, 1);
	glTranslatef( 0,0,-m_baseradius/2 );

	glTranslatef(1.0f,0,m_baseradius/2-1.0f);
	glRotatef(90, 0.0, 1.0, 0.0);
	gluCylinder(quadratic, m_baseradius/4, m_baseradius/4, 0.5f, 8, 1);
	//draw the first cap
	gluQuadricOrientation(quadratic,GLU_INSIDE);
	gluDisk( quadratic, 0.0, m_baseradius/4, 16, 1);
	glTranslatef( 0,0,0.5f );
	//draw the second cap
	gluQuadricOrientation(quadratic,GLU_OUTSIDE);
	gluDisk( quadratic, 0.0, m_baseradius/4, 16, 1);
	glPopMatrix();

	//3----------------------------------
	glPushMatrix();
	glTranslatef(0,m_baseradius-2+0.707f*(m_baseradius+2),0.707f*(m_baseradius+2));
	glRotatef(-m_zeta1*360/TwoPi, 1.0, 0.0, 0.0);
	gluCylinder(quadratic, 1.0f, 1.0f, m_baseradius, 8, 1);
	glTranslatef(0,0,m_baseradius);
	gluSphere(quadratic, 1.2f, 12, 6);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,m_baseradius-2+0.707f*(m_baseradius+2)+m_baseradius*sin(m_zeta1),0.707f*(m_baseradius+2)+m_baseradius*cos(m_zeta1));
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(quadratic, 1.0f, 1.0f, m_baseradius/2, 8, 1);
	//draw the end cap
	glTranslatef( 0,0,m_baseradius/2 );
	gluQuadricOrientation(quadratic,GLU_OUTSIDE);
	gluDisk( quadratic, 0.0, 1.0f, 16, 1);
	glTranslatef( 0,0,-m_baseradius/2 );
	
	glTranslatef(-0.65f,-1.0,m_baseradius/2-1.0f);
	glRotatef(90, 1.0, 0.0, 0.0);
	gluCylinder(quadratic, m_baseradius/4, m_baseradius/4, 0.5f, 8, 1);
	//draw the first cap
	gluQuadricOrientation(quadratic,GLU_INSIDE);
	gluDisk( quadratic, 0.0, m_baseradius/4, 16, 1);
	glTranslatef( 0,0,0.5f );
	//draw the second cap
	gluQuadricOrientation(quadratic,GLU_OUTSIDE);
	gluDisk( quadratic, 0.0, m_baseradius/4, 16, 1);
	glPopMatrix();

	//4----------------------------------
	glPushMatrix();
	glTranslatef(0,-m_baseradius+2-0.707f*(m_baseradius+2),0.707f*(m_baseradius+2));
	glRotatef(m_zeta3*360/TwoPi, 1.0, 0.0, 0.0);
	gluCylinder(quadratic, 1.0f, 1.0f, m_baseradius, 8, 1);
	glTranslatef(0,0,m_baseradius);
	gluSphere(quadratic, 1.2f, 12, 6);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,-m_baseradius+2-0.707f*(m_baseradius+2)-m_baseradius*sin(m_zeta3),0.707f*(m_baseradius+2)+m_baseradius*cos(m_zeta3));
	glRotatef(90, 1.0, 0.0, 0.0);
	gluCylinder(quadratic, 1.0f, 1.0f, m_baseradius/2, 8, 1);
	//draw the end cap
	glTranslatef( 0,0,m_baseradius/2 );
	gluQuadricOrientation(quadratic,GLU_OUTSIDE);
	gluDisk( quadratic, 0.0, 1.0f, 16, 1);
	glTranslatef( 0,0,-m_baseradius/2 );

	glTranslatef(0.65f,1.0,m_baseradius/2-1.0f);
	glRotatef(90, 1.0, 0.0, 0.0);
	gluCylinder(quadratic, m_baseradius/4, m_baseradius/4, 0.5f, 8, 1);
	//draw the first cap
	gluQuadricOrientation(quadratic,GLU_INSIDE);
	gluDisk( quadratic, 0.0, m_baseradius/4, 16, 1);
	glTranslatef( 0,0,0.5f );
	//draw the second cap
	gluQuadricOrientation(quadratic,GLU_OUTSIDE);
	gluDisk( quadratic, 0.0, m_baseradius/4, 16, 1);
	glPopMatrix();

	glPopMatrix();
}

void Spinner::Update(float dt, int numFrames)
{
	w = w + (speed * TwoPi);
	if (w >= TwoPi) {
		w = w - TwoPi;
	}

	m_phi = 30 * TwoPi/360.0f * cos(8 * dt*numFrames);

	m_zeta0 = 90 + -45 * TwoPi/360.0f * cos(4 * dt*numFrames);
	m_zeta1 = 90 + -45 * TwoPi/360.0f * cos(4 * dt*numFrames + 22.5f);
	m_zeta2 = 90 + -45 * TwoPi/360.0f * cos(4 * dt*numFrames + 45.0f);
	m_zeta3 = 90 + -45 * TwoPi/360.0f * cos(4 * dt*numFrames + 67.5f);
}
