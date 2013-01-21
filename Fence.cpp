/*
* Modifications by Steve Coward
* Portland State University CS547
* steve-coward@comcast.net
*/

#include "Fence.h"
#include "SurfRev.h"
#include "ProjUtils.h"
#include "Mesh.h"
#include <stdio.h>
#include <FL/math.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>


Fence::Fence()
{
	initialized = false;
}

// Destructor
Fence::~Fence(void)
{
if ( initialized )
    {
		glDeleteLists(dlFence, 1);
    }
}
bool Fence::Initialize(bool bUseTexCoor)
{
	ubyte *image_data;
	int image_height, image_width;

    // Load the image for the texture.
    if ( ! ( image_data = (ubyte*)tga_load("wood.tga", &image_width,
					   &image_height, TGA_TRUECOLOR_24) ) )
    {
		fprintf(stderr, "Fence::Initialize: Couldn't load wood.tga\n");
		return false;
    }

	// This sets a parameter for how the texture is loaded and interpreted.
    // basically, it says that the data is packed tightly in the image array.
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	// This creates a texture object and binds it, so the next few operations
    // apply to this texture.
	glEnable(GL_DEPTH_TEST);
	glGenTextures(1, &m_texFence);
    glBindTexture(GL_TEXTURE_2D, m_texFence);

    // This sets up the texture with high quality filtering. First it builds
    // mipmaps from the image data, then it sets the filtering parameters
    // and the wrapping parameters. We want the grass to be repeated over the
    // ground.
    gluBuild2DMipmaps(GL_TEXTURE_2D,3, image_width, image_height, 
		      GL_RGB, GL_UNSIGNED_BYTE, image_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	m_pMesh = new Mesh();
	m_pMesh->bUseTexCoors = bUseTexCoor;
	
	m_pMesh->readFile("fence.x");
	if (bUseTexCoor) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_texFence);
		// This says what to do with the texture. Modulate will multiply the
		// texture by the underlying color.
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}
	m_pMesh->Initialize();
	m_pMesh->bUseTexCoors = bUseTexCoor;

	dlFence = glGenLists(1);
	glNewList(dlFence, GL_COMPILE);
	
	if (bUseTexCoor) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_texFence);
		// This says what to do with the texture. Modulate will multiply the
		// texture by the underlying color.
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}

	glPushMatrix();
	glTranslatef(-13,0,0);
	m_pMesh->draw();
	glTranslatef(-10,0,0);
	m_pMesh->draw();
	glRotatef(-90,0,0,1);
	glTranslatef(-17,0,0);
	m_pMesh->draw();
	glTranslatef(-10,0,0);
	m_pMesh->draw();
	glTranslatef(-10,0,0);
	m_pMesh->draw();
	glTranslatef(-10,0,0);
	m_pMesh->draw();
	glTranslatef(-10,0,0);
	m_pMesh->draw();
	glTranslatef(-10,0,0);
	m_pMesh->draw();
	glTranslatef(-10,0,0);
	m_pMesh->draw();
	glTranslatef(-10,0,0);
	m_pMesh->draw();
	glRotatef(-90,0,0,1);
	glTranslatef(-17,0,0);
	m_pMesh->draw();
	glTranslatef(-10,0,0);
	m_pMesh->draw();
	glRotatef(-90,0,0,1);
	glTranslatef(-17,0,0);
	m_pMesh->draw();
	glTranslatef(-10,0,0);
	m_pMesh->draw();
	glTranslatef(-10,0,0);
	m_pMesh->draw();
	glTranslatef(-10,0,0);
	m_pMesh->draw();
	glTranslatef(-10,0,0);
	m_pMesh->draw();
	glTranslatef(-30,0,0);
	m_pMesh->draw();
	glPopMatrix();
	
	if (bUseTexCoor) {
		glDisable(GL_TEXTURE_2D);
	}
	glEndList();

	initialized = true;

	return(true);
}
void Fence::Draw()
{
	glColor3f(1.0,1.0,1.0);
	glCallList(dlFence);
}