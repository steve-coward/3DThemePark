#ifndef _FENCE_H_
#define _FENCE_H_

#include <Fl/gl.h>
#include <gl/glu.h>
#include "libtarga.h"
#include "ProjUtils.h"
#include "Mesh.h"
#include <list>
#include <vector>

class Fence {
public:
	// Constructor
	Fence();

	// Destructor
	~Fence(void);

	bool Initialize(bool bUseTexCoor);
	void Draw();
	Mesh* m_pMesh;
	GLubyte dlFence;

private:
	GLuint m_texFence; // The object for the Fence texture.
	bool initialized; // Whether or not we have been initialized.
};

#endif // _FENCE_H_