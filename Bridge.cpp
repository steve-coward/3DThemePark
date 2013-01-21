/*
* Modifications by Steve Coward
* Portland State University CS547
* steve-coward@comcast.net
*/


#include "Bridge.h"
#include "ProjUtils.h"
#include "PolySweep.h"
#include <stdio.h>
#include <FL/math.h>
#include <gl/glu.h>
#include <list>

Bridge::Bridge(GLfloat cx, GLfloat cy, GLfloat width, GLfloat length, GLfloat radius, Ground* pGround)
{
	initialized = false;
	m_pGround = pGround;
	m_cx = cx;
	m_cy = cy;
	m_cz = m_pGround->GetHeight(m_cx+m_pGround->m_parkWidth/2, m_cy+m_pGround->m_parkLength/2);
	m_width = width;
	m_length = length;
	m_radius = radius;
};

// Destructor
Bridge::~Bridge(void)
{
    if ( initialized )
    {
		glDeleteLists(bridge_list, 1);
    }
}



// Initializer. Would return false if anything could go wrong.
bool Bridge::Initialize(void)
{
	float p[3];
    float lp[3];
	float lastheight;
	float radial[3];
	float thisheight;
	ubyte *image_data;
	int image_height, image_width;

    // Load the image for the texture.
    if ( ! ( image_data = (ubyte*)tga_load("wood.tga", &image_width,
					   &image_height, TGA_TRUECOLOR_24) ) )
    {
		fprintf(stderr, "Bridge::Initialize: Couldn't load wood.tga\n");
		return false;
    }

	// This sets a parameter for how the texture is loaded and interpreted.
    // basically, it says that the data is packed tightly in the image array.
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	// This creates a texture object and binds it, so the next few operations
    // apply to this texture.
	glGenTextures(1, &texBridge);
    glBindTexture(GL_TEXTURE_2D, texBridge);

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
	
	PolySweep* m_pBridgeArch;
	PolySweep* m_pBridgeRail;
	PolySweep* m_pBridgeXTie;
	std::list<PolySweep*>::iterator itr;

	m_pBridgeArch = new PolySweep(&Curve2DQuadratic, &Curve2DQuadraticP, m_radius, m_radius, 12, 12, 0.0f, 2.0f*m_radius, false, true);
	m_pBridgeArch->Initialize();
	m_pBridgeRail = new PolySweep(&Curve2DConstant, &Curve2DZero, 1.0f, 1.0f, 1, 1, 0.0f, 5.0f*m_radius, false, true);
	m_pBridgeRail->Initialize();
	m_pBridgeXTie = new PolySweep(&Curve2DConstant, &Curve2DZero, 1.0f, 1.0f, 1, 1, 0.0f, 1.4f*m_width, true, true);
	m_pBridgeXTie->Initialize();
	//m_listFoliage.push_back(m_pSurfRevFoliage);

	// Create the display list for the track - just a set of line segments
	// We just use curve evaluated at integer paramer values, because the
	// subdivision has made sure that these are good enough.
	bridge_list = glGenLists(1);
	glNewList(bridge_list, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texBridge);
	// This says what to do with the texture. Modulate will multiply the
    // texture by the underlying color.
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Create bridge structure
	// Direction of creation of structure is counter clockwise as seen from above.
	// glRotate follows the right-hand rule, so if the vector (x, y, z) points toward
	// the user, the rotation will be counter clockwise. 
	glPushMatrix();


	glPushMatrix();
	glTranslatef(0.0f, 1.0f, -2.0);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	m_pBridgeArch->Draw();
	glTranslatef(0.0f, 0.0f, m_width);
	m_pBridgeArch->Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5.0f, 0.0f, -2.0f);
	m_pBridgeRail->Draw();
	glTranslatef(0.0f, m_width, 0.0f);
	m_pBridgeRail->Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-8.0f, 0.5f, -1.0f);
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	for (int i=0;i<m_length;i+=1.25f) {
		glTranslatef(0.0f, -1.25f, 0.0f);
		m_pBridgeXTie->Draw();
	}
	glPopMatrix();

	glPopMatrix();

    glDisable(GL_TEXTURE_2D);
	glEndList();

	initialized = true;

	return true;
}


// Draw
void Bridge::Draw(void)
{
    if ( ! initialized )
		return;

    // Draw the track
    glColor3f(1.0,1.0,1.0);
	glCallList(bridge_list);
}


void Bridge::Update(float dt)
{
	if ( ! initialized ) {
		return;
	}
}


