/*
* Modifications by Steve Coward
* Portland State University CS547
* steve-coward@comcast.net
*/

#include "Tree.h"
#include "SurfRev.h"
#include "ProjUtils.h"
//#include "Mesh.h"
#include <stdio.h>
#include <FL/math.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>


// Better to have a few randomized tree versions
// and then have multiple, randomly placed copies of each
// type.  This would save some memory.
Tree::Tree(float x, float y, float z)
{
	height = (float)(rand() % 120)/10.0f + 5.0f;
	radius = (float)(rand() % 15)/10.0f + 1.5f;
	clearance = (float)(rand() % 20)/10.0f + 0.75f;
	trunk_radius = (float)(rand() % 12)/10.0f + 0.35f;
	trunk_height = (float)(rand() % 20)/10.0f + 5.0f;
	color[0] = 0.0f;
	color[1] = 0.6f;
	color[2] = 0.0f;
	trunk_color[0] = 0.65f;
	trunk_color[1] = 0.48f;
	trunk_color[2] = 0.36f;
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
}

// Destructor
Tree::~Tree(void)
{
}

void Tree::Init()
{
	SurfRev* m_pSurfRevFoliage;
	std::list<SurfRev*>::iterator itr;

	for (int i = 0;i<6;i++) {
		m_pSurfRevFoliage = new SurfRev(&Curve2DQuadratic, &Curve2DZero, radius*((6.0f-(float)i)/6.0f), height*((6.0f-(float)i)/6.0f), 16, 6);
		m_pSurfRevFoliage->Initialize();
		m_listFoliage.push_back(m_pSurfRevFoliage);
	}
	m_pSurfRevTrunk = new SurfRev(&Curve2DLinear, &Curve2DZero, trunk_radius, trunk_height, 12, 8);
	m_pSurfRevTrunk->Initialize();

	m_dlTree = glGenLists(1);
    glNewList(m_dlTree, GL_COMPILE);
	
	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]+clearance);
	itr = m_listFoliage.begin();
	int i = 0;
	while (itr != m_listFoliage.end()) {
		glColor3f(color[0], color[1]+(i*0.1f), color[2]+((i&1)*0.2f));
		glTranslatef(0,0,+height/6.0f);
		(*itr)->Draw();
		++itr;
		i++;
	}
	glTranslatef(0,0,-clearance-height);
	glColor3fv(trunk_color);
	m_pSurfRevTrunk->Draw();
	glPopMatrix();
	
	glEndList();
}

void Tree::Draw()
{
	glCallList(m_dlTree);
}
