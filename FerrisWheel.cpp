/*
* Modifications by Steve Coward
* Portland State University CS547
* steve-coward@comcast.net
*
* Class file for the WorldWindow class.
 */

#include "FerrisWheel.h"
#include "ProjUtils.h"
#include <stdio.h>
#include <FL/math.h>
#include <gl/glu.h>
#include "libtarga.h"
#include <stdlib.h>
#include <iostream>

// The carriage energy and mass
const float FerrisWheel::FERRISWHEEL_ENERGY = 125.0f;


// Constructor
FerrisWheel::FerrisWheel(GLfloat x, GLfloat y, GLfloat z, GLfloat orient, GLfloat radius)
{
	halfwidth = 2;
	offset = 4;
	m_radius = radius;
	w = 0.0;
	m_pos[0] = x;
	m_pos[1] = y;
	m_pos[2] = z + m_radius + offset; // add offset so carriage does not scrape the ground
	m_theta = orient;

	initialized = false;
	speed = 0.0025f; // revs per update

	quadratic=gluNewQuadric(); // Create A Pointer To The Quadric Object ( NEW )
	gluQuadricNormals(quadratic, GLU_SMOOTH); // Create Smooth Normals ( NEW )
	gluQuadricTexture(quadratic, GL_TRUE); // Create Texture Coords ( NEW )

};

// Destructor
FerrisWheel::~FerrisWheel(void)
{
    if ( initialized )
    {
		glDeleteLists(dlCarriage, 1);
		glDeleteLists(dlWheel, 1);
		glDeleteLists(dlSupport, 1);
    }
}


// Initializer. Would return false if anything could go wrong.
bool
FerrisWheel::Initialize(void)
{
	ubyte   *image_data;
    int	    image_height, image_width;
	
    // Load the image for the texture. The texture file has to be in
    // a place where it will be found.
    if ( ! ( image_data = (ubyte*)tga_load("stripe.tga", &image_width,
					   &image_height, TGA_TRUECOLOR_24) ) )
    {
		fprintf(stderr, "FerrisWheel::Initialize: Couldn't load stripe.tga\n");
		return false;
    }

	// This sets a parameter for how the texture is loaded and interpreted.
    // basically, it says that the data is packed tightly in the image array.
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	// This creates a texture object and binds it, so the next few operations
    // apply to this texture.
	glGenTextures(1, &texFerrisWheel);
    glBindTexture(GL_TEXTURE_2D, texFerrisWheel);


    // This sets up the texture with high quality filtering. First it builds
    // mipmaps from the image data, then it sets the filtering parameters
    // and the wrapping parameters. We want the grass to be repeated over the
    // ground.
    gluBuild2DMipmaps(GL_TEXTURE_2D,3, image_width, image_height, 
		      GL_RGB, GL_UNSIGNED_BYTE, image_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		    GL_NEAREST_MIPMAP_LINEAR);

	// Set up the train. At this point a cube is drawn. NOTE: The
    // x-axis will be aligned to point along the track. The origin of the
    // train is assumed to be at the bottom of the train.
    dlCarriage = glGenLists(1);
    glNewList(dlCarriage, GL_COMPILE);
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.4f*halfwidth, 0.8f*halfwidth, 1.0f);
	glVertex3f(-0.4f*halfwidth, 0.8f*halfwidth, 1.0f);
	glVertex3f(-0.4f*halfwidth, -0.8f*halfwidth, 1.0f);
	glVertex3f(0.4f*halfwidth, -0.8f*halfwidth, 1.0f);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0.4f*halfwidth, -0.8f*halfwidth, 0.0f);
	glVertex3f(-0.4f*halfwidth, -0.8f*halfwidth, 0.0f);
	glVertex3f(-0.4f*halfwidth, 0.8f*halfwidth, 0.0f);
	glVertex3f(0.4f*halfwidth, 0.8f*halfwidth, 0.0f);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.4f*halfwidth, 0.8f*halfwidth, 0.0f);
	glVertex3f(0.4f*halfwidth, 0.8f*halfwidth, 1.0f);
	glVertex3f(0.4f*halfwidth, -0.8f*halfwidth, 1.0f);
	glVertex3f(0.4f*halfwidth, -0.8f*halfwidth, 0.0f);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.4f*halfwidth, 0.8f*halfwidth, 1.0f);
	glVertex3f(-0.4f*halfwidth, 0.8f*halfwidth, 0.0f);
	glVertex3f(-0.4f*halfwidth, -0.8f*halfwidth, 0.0f);
	glVertex3f(-0.4f*halfwidth, -0.8f*halfwidth, 1.0f);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.4f*halfwidth, 0.8f*halfwidth, 1.0f);
	glVertex3f(0.4f*halfwidth, 0.8f*halfwidth, 0.0f);
	glVertex3f(-0.4f*halfwidth, 0.8f*halfwidth, 0.0f);
	glVertex3f(-0.4f*halfwidth, 0.8f*halfwidth, 1.0f);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.4f*halfwidth, -0.8f*halfwidth, 0.0f);
	glVertex3f(0.4f*halfwidth, -0.8f*halfwidth, 1.0f);
	glVertex3f(-0.4f*halfwidth, -0.8f*halfwidth, 1.0f);
	glVertex3f(-0.4f*halfwidth, -0.8f*halfwidth, 0.0f);
    glEnd();
    glEndList();

	dlWheel = glGenLists(1);
    glNewList(dlWheel, GL_COMPILE);
	
	//--------------------
	// Draw two hoops
	//--------------------
	glColor3f(1.0, 1.0, 1.0);
	
	glPushMatrix();
	glTranslatef(0, -halfwidth, 0);
	glRotatef(90, 1.0, 0.0, 0.0); // in degrees
	DrawTorus(m_radius, 0.25, 36, 36);
    glPopMatrix();
	glPushMatrix();
	glTranslatef(0, halfwidth, 0);
	glRotatef(90, 1.0, 0.0, 0.0); // in degrees
	DrawTorus(m_radius, 0.25, 36, 36);
    glPopMatrix();

	//--------------------
	// Draw struts and axle
	//--------------------
	// center axle
	glPushMatrix();
	glTranslatef(0, halfwidth+2, 0); // +2 since local origin is at bottom of cylinder
	glRotatef(90, 1.0, 0.0, 0.0); // in degrees
	gluCylinder(quadratic,0.25f,0.25f,8.0f,32,32);
	glPopMatrix();
	
	// outer strut connecting hoops
	// Translate the carriage to the bottom of the ferris wheel
	glPushMatrix();
	glTranslatef(0, halfwidth, 0); // +2 since local origin is at bottom of cylinder
	glTranslatef(m_radius*sin(w), 0, -m_radius*cos(w));
	glRotatef(90, 1.0, 0.0, 0.0); // in degrees
	gluCylinder(quadratic,0.25f,0.25f,4.0f,32,32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, halfwidth, 0); // +2 since local origin is at bottom of cylinder
	glTranslatef(m_radius*sin(w+TwoPi/4.0f), 0, -m_radius*cos(w+TwoPi/4.0f));
	glRotatef(90, 1.0, 0.0, 0.0); // in degrees
	gluCylinder(quadratic,0.25f,0.25f,4.0f,32,32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, halfwidth, 0); // +2 since local origin is at bottom of cylinder
	glTranslatef(m_radius*sin(w+TwoPi/2.0f), 0, -m_radius*cos(w+TwoPi/2.0f));
	glRotatef(90, 1.0, 0.0, 0.0); // in degrees
	gluCylinder(quadratic,0.25f,0.25f,4.0f,32,32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, halfwidth, 0); // +2 since local origin is at bottom of cylinder
	glTranslatef(m_radius*sin(w+3.0f*TwoPi/4.0f), 0, -m_radius*cos(w+3.0f*TwoPi/4.0f));
	glRotatef(90, 1.0, 0.0, 0.0); // in degrees
	gluCylinder(quadratic,0.25f,0.25f,4.0f,32,32);
	glPopMatrix();

	//--------------------
	// Draw spokes
	//--------------------
	glPushMatrix();
	glTranslatef(0, halfwidth, 0); // +2 since local origin is at bottom of cylinder
	glRotatef(30-w*360/TwoPi, 0.0, 1.0, 0.0);
	gluCylinder(quadratic,0.25f,0.25f,m_radius,32,32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, halfwidth, 0); // +2 since local origin is at bottom of cylinder
	glRotatef(150-w*360/TwoPi, 0.0, 1.0, 0.0);
	gluCylinder(quadratic,0.25f,0.25f,m_radius,32,32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, halfwidth, 0); // +2 since local origin is at bottom of cylinder
	glRotatef(270-w*360/TwoPi, 0.0, 1.0, 0.0);
	gluCylinder(quadratic,0.25f,0.25f,m_radius,32,32);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, halfwidth, 0); // -2 since local origin is at bottom of cylinder
	glRotatef(90-w*360/TwoPi, 0.0, 1.0, 0.0);
	gluCylinder(quadratic,0.25f,0.25f,m_radius,32,32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0-halfwidth, 0); // -2 since local origin is at bottom of cylinder
	glRotatef(210-w*360/TwoPi, 0.0, 1.0, 0.0);
	gluCylinder(quadratic,0.25f,0.25f,m_radius,32,32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -halfwidth, 0); // -2 since local origin is at bottom of cylinder
	glRotatef(330-w*360/TwoPi, 0.0, 1.0, 0.0);
	gluCylinder(quadratic,0.25f,0.25f,m_radius,32,32);
	glPopMatrix();

	glEndList();


	dlSupport = glGenLists(1);
    glNewList(dlSupport, GL_COMPILE);
	
	//--------------------
	// Draw supports
	//--------------------

	glPushMatrix();
	glTranslatef(0, -halfwidth-1, 0); // -2 since local origin is at bottom of cylinder
	glRotatef(225, 0.0, 1.0, 0.0);
	glShadeModel(GL_SMOOTH);
	gluQuadricTexture(quadratic, GL_TRUE);
	gluQuadricDrawStyle(quadratic, GLU_FILL);
	gluQuadricNormals(quadratic, GLU_SMOOTH);      // Create Smooth Normals 
	gluCylinder(quadratic,0.25f,0.25f,1.414f*(m_radius+offset),32,32);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -halfwidth-1, 0); // -2 since local origin is at bottom of cylinder
	glRotatef(135, 0.0, 1.0, 0.0);
	gluCylinder(quadratic,0.25f,0.25f,1.414f*(m_radius+offset),32,32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, halfwidth+1, 0); // -2 since local origin is at bottom of cylinder
	glRotatef(225, 0.0, 1.0, 0.0);
	gluCylinder(quadratic,0.25f,0.25f,1.414f*(m_radius+offset),32,32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, halfwidth+1, 0); // -2 since local origin is at bottom of cylinder
	glRotatef(135, 0.0, 1.0, 0.0);
	gluCylinder(quadratic,0.25f,0.25f,1.414f*(m_radius+offset),32,32);
	glPopMatrix();

	glEndList();

	
	initialized = true;

    return true;
}


// Draw
void FerrisWheel::Draw(void)
{
	float TwoPi=2*4*atan(1.0f);

    if ( ! initialized )
	return;

	// This creates a texture object and binds it, so the next few operations
    // apply to this texture.
    glEnable(GL_TEXTURE_2D);

	// This says what to do with the texture. Modulate will multiply the
    // texture by the underlying color.
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
    glBindTexture(GL_TEXTURE_2D, texFerrisWheel);

	glPushMatrix();
	glTranslatef(m_pos[0], m_pos[1], m_pos[2]);
	glCallList(dlSupport);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(m_pos[0], m_pos[1], m_pos[2]);
	glRotatef(w*360/TwoPi, 0.0, 1.0, 0.0);
	glCallList(dlWheel);
	glPopMatrix();
	
	//--------------------
	// Draw carriage
	//--------------------
	glPushMatrix();

    // Translate the carriage to the center of the ferris wheel
	glTranslatef(m_pos[0], m_pos[1], m_pos[2]);
	
	// Translate the carriage to the edge of the ferris wheel
	glTranslatef(m_radius*cos(w), 0, -m_radius*sin(w));

    // translate the carriage so that it hangs under support
	glTranslatef(0.0f, 0.0f, -1.75f);

	// Rotate carriage to simulate swinging
	glRotatef(m_phi * 360.0f/TwoPi, 0.0, 1.0, 0.0);

	// Draw the carriage
    glCallList(dlCarriage);

    glPopMatrix();
	
	glDisable(GL_TEXTURE_2D);
}


void FerrisWheel::Update(float dt, int numFrames)
{
    if ( ! initialized )
	return;

	w = w + (speed * TwoPi);
	if (w >= TwoPi) {
		w = w - TwoPi;
	}

	m_phi = 15 * TwoPi/360.0f * cos(8 * dt*numFrames);
}

void FerrisWheel::DrawTorus(float majorRadius, float minorRadius, int numMajor, int numMinor)
{
	GLfloat vNormal[3];
	double majorStep = TwoPi / numMajor;
	double minorStep = TwoPi / numMinor;
	int i, j;
	
	for (i = 0; i < numMajor; i++)
	{
		double a0 = i * majorStep;
		double a1 = a0 + majorStep;
		float x0 = (float)cos(a0);
		float y0 = (float)sin(a0);
		float x1 = (float)cos(a1);
		float y1 = (float)sin(a1);

		glBegin(GL_TRIANGLE_STRIP);
		for (j = 0; j <= numMinor; j++)
		{
			double b = j * minorStep;
			float c = (float)cos(b);
			float r = minorRadius * c + majorRadius;
			float z = minorRadius * (float)sin(b);

			//First point
			glTexCoord2f((float)i / (float)(numMajor), (float)(j) / (float)(numMinor));
			vNormal[0] = x0 * c;
			vNormal[1] = y0 * c;
			vNormal[2] = z / minorRadius;
			ReduceToUnit(vNormal);
			glNormal3f(vNormal[0], vNormal[1], vNormal[2]);
			glVertex3f(x0 * r, y0 * r, z);

			glTexCoord2f((float)(i + 1) / (float)(numMajor), (float)(j) / (float)(numMinor));
			vNormal[0] = x1 * c;
			vNormal[1] = y1 * c;
			vNormal[2] = z / minorRadius;
			ReduceToUnit(vNormal);
			glNormal3f(vNormal[0], vNormal[1], vNormal[2]);
			glVertex3f(x1 * r, y1 * r, z);
		}
		glEnd();
	}

}

void FerrisWheel::ReduceToUnit(float vector[3])					// Reduces A Normal Vector (3 Coordinates)
{									// To A Unit Normal Vector With A Length Of One.
	float length;							// Holds Unit Length
	// Calculates The Length Of The Vector
	length = (float)sqrt((vector[0]*vector[0]) + (vector[1]*vector[1]) + (vector[2]*vector[2]));

	if(length == 0.0f)						// Prevents Divide By 0 Error By Providing
		length = 1.0f;						// An Acceptable Value For Vectors To Close To 0.

	vector[0] /= length;						// Dividing Each Element By
	vector[1] /= length;						// The Length Results In A
	vector[2] /= length;						// Unit Normal Vector.
}

