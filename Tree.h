#ifndef _TREE_H_
#define _TREE_H_

#include <Fl/gl.h>
#include <gl/glu.h>
#include "libtarga.h"
#include "ProjUtils.h"
#include "SurfRev.h"
#include "Mesh.h"
#include <list>
#include <vector>

class Tree {
public:
	// Constructor
	Tree(float x, float y, float z);

	// Destructor
	~Tree(void);

	void Init();
	void Draw();
	GLubyte m_dlTree;

private:
	SurfRev* m_pSurfRevTrunk;
	std::list<SurfRev*> m_listFoliage;
	float height;
	float radius;
	float clearance;
	float trunk_radius;
	float trunk_height;
	float color[3];
	float trunk_color[3];
	float pos[3];
};

#endif // _TREE_H_