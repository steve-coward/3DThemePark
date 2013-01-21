/*
* Modifications by Steve Coward
* Portland State University CS547
* steve-coward@comcast.net
*
* CS559 Maze Project
*
* Class file for the WorldWindow class.
*
* (c) Stephen Chenney, University of Wisconsin at Madison, 2001-2002
*
 * Ground.cpp: A class for drawing the ground.
 *
 * (c) 2001-2002: Stephen Chenney, University of Wisconsin at Madison.
 */


#include "Ground.h"
#include "libtarga.h"
#include "ProjUtils.h"
#include "math.h"
#include <stdio.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <time.h>

// Destructor
Ground::~Ground(void)
{
    if ( initialized )
    {
	glDeleteLists(display_list, 1);
	glDeleteTextures(1, &groundTexture);
    }
}



GLfloat Ground::GetHeight(GLfloat x, GLfloat y)
{
	if (m_bUseHeightMap) {
		ubyte* pixel;
		GLfloat h;
		int xp, yp;
		
		xp = (int)(m_heightmap_width / (int)(m_parkWidth) * x);
		
		yp = (int)(m_heightmap_height/ (int)(m_parkLength) * y);

		pixel = m_heightmap + (yp * m_heightmap_width + xp)*3;
		h = floor((float)pixel[0]/m_heightscale);
		return(h);
	}
	else {
		return(0);
	}
}

// Initializer. Returns false if something went wrong, like not being able to
// load the texture.
bool Ground::Initialize(void)
{
    ubyte   *image_data;
    int	    image_height, image_width;

    // GROUND
	// Load the image for the texture. The texture file has to be in
    // a place where it will be found.
    if ( ! ( image_data = (ubyte*)tga_load("terrain3.tga", &image_width,
					   &image_height, TGA_TRUECOLOR_24) ) )
    {
	fprintf(stderr, "Ground::Initialize: Couldn't load terrain3.tga\n");
	return false;
    }

    // This creates a texture object and binds it, so the next few operations
    // apply to this texture.
    glGenTextures(1, &groundTexture);
    glBindTexture(GL_TEXTURE_2D, groundTexture);

	// This sets a parameter for how the texture is loaded and interpreted.
	// basically, it says that the data is packed tightly in the image array.
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

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

	// CLIFF
	// Load the image for the texture. The texture file has to be in
    // a place where it will be found.
    if ( ! ( image_data = (ubyte*)tga_load("cliff.tga", &image_width,
					   &image_height, TGA_TRUECOLOR_24) ) )
    {
	fprintf(stderr, "Ground::Initialize: Couldn't load cliff.tga\n");
	return false;
    }

    // This creates a texture object and binds it, so the next few operations
    // apply to this texture.
    glGenTextures(1, &cliffTexture);
    glBindTexture(GL_TEXTURE_2D, cliffTexture);

	// This sets a parameter for how the texture is loaded and interpreted.
	// basically, it says that the data is packed tightly in the image array.
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

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

	// This says what to do with the texture. Modulate will multiply the
	// texture by the underlying color.
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 

	// Now do the geometry. Create the display list.
	display_list = glGenLists(1);
	glNewList(display_list, GL_COMPILE);
	// Use white, because the texture supplies the color.
	glColor3f(1.0, 1.0, 1.0);

	// The surface normal is up for the ground.
	// Well not really.
	glNormal3f(0.0, 0.0, 1.0);

	// Turn on texturing and bind the grass texture.
	glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, cliffTexture);

	if (true) {
		// Draw the ground as triangle strips, specifying texture coordinates.
		// Note that every other texture mapping is upside down.
		// This is due to sharing of two vertices (and hence texture coordinates)
		// between successive triangles in the strip.
		GLfloat h1, h2, h3, h4;
		int vstride = 4;
		int tstride = m_heightmap_width * vstride / (int)m_parkWidth; // Assuming all is square

		for (int y = -(int)m_parkLength/2, j = 0;y < (int)m_parkLength/2; y+=vstride, j += tstride) {
			for (int x = -(int)m_parkWidth/2, i = 0;x < (int)m_parkWidth/2; x+=vstride, i += tstride) {
				// Place 2 triangles, forming square
			
				h2 = GetHeight(x+m_parkWidth/2, y+m_parkLength/2);
				h1 = GetHeight(x+m_parkWidth/2, y+m_parkLength/2+vstride);
				h3 = GetHeight(x+m_parkWidth/2+vstride, y+m_parkLength/2+vstride);
				h4 = GetHeight(x+m_parkWidth/2+vstride, y+m_parkLength/2);

				if (abs(h1-h3) < 5.0f) {
					glBindTexture(GL_TEXTURE_2D, groundTexture);
				}
				else {
					glBindTexture(GL_TEXTURE_2D, groundTexture);
				}
				glBegin(GL_TRIANGLES);
				
				//  1(x,y+d)    3(x+d,y+d)
				//  2(x,y)      4(x+d,y)
				//
				// First Triangle 1-2-3
				// 1
				//if (abs(h1-h3) < 1) {
					glTexCoord2f((float)(i)/m_heightmap_width, (float)(j+tstride)/m_heightmap_height);
				//}
				//else {
				//	glTexCoord2f(0.0f, 0.0f);
				//}
				glNormal3f(0.0, 0.0, 1.0);
				glVertex3f((float)(x), (float)(y+vstride), h1);

				// 2
				//if (abs(h1-h3) < 2) {
					glTexCoord2f((float)(i)/m_heightmap_width, (float)(j)/m_heightmap_height);
				//}
				//else {
				//	glTexCoord2f((float)(4.0f*tstride)/m_heightmap_height, 0.0f);
				//}
				glNormal3f(0.0, 0.0, 1.0);
				glVertex3f((float)(x), (float)(y), h2);

				// 3
				//if (abs(h1-h3) < 2) {
					glTexCoord2f((float)(i+tstride)/m_heightmap_width, (float)(j+tstride)/m_heightmap_height);
				//}
				//else {
				//	glTexCoord2f(0.0f, (float)(4.0f*h3*m_heightscale)/m_heightmap_height);
				//}
				glNormal3f(0.0, 0.0, 1.0);
				glVertex3f((float)(x+vstride), (float)(y+vstride), h3);
				glEnd();


				// Second Triangle 2-4-3
				if (abs(h2-h4) < 5.0f) {
					glBindTexture(GL_TEXTURE_2D, groundTexture);
				}
				else {
					glBindTexture(GL_TEXTURE_2D, groundTexture);
				}
				glBegin(GL_TRIANGLES);
				
				// 2
				//if (abs(h1-h3) < 2) {
					glTexCoord2f((float)(i)/m_heightmap_width, (float)(j)/m_heightmap_height);
				//}
				//else {
				//	glTexCoord2f((float)(4.0f*tstride)/m_heightmap_height, 0.0f);
				//}
				glNormal3f(0.0, 0.0, 1.0);
				glVertex3f((float)(x), (float)(y), h2);


				// 4
				//if (abs(h1-h3) < 2) {
					glTexCoord2f((float)(i+tstride)/m_heightmap_width, (float)(j)/m_heightmap_height);
				//}
				//else {
				//	glTexCoord2f((float)(4.0f*tstride)/m_heightmap_height, (float)(4.0f*h3*m_heightscale)/m_heightmap_height);
				//}
				glNormal3f(0.0, 0.0, 1.0);
				glVertex3f((float)(x+vstride), (float)(y), h4);

				// 3
				//if (abs(h1-h3) < 2) {
					glTexCoord2f((float)(i+tstride)/m_heightmap_width, (float)(j+tstride)/m_heightmap_height);
				//}
				//else {
				//	glTexCoord2f(0.0f, (float)(4.0f*h3*m_heightscale)/m_heightmap_height);
				//}
				glNormal3f(0.0, 0.0, 1.0);
				glVertex3f((float)(x+vstride), (float)(y+vstride), h3);

				glEnd();
				//break;
			}
		}
	}

	// Turn texturing off again, because we don't want everything else to
	// be textured.
	glDisable(GL_TEXTURE_2D);
    glEndList();

    // We only do all this stuff once, when the GL context is first set up.
    initialized = true;

    return true;
}

bool Ground::InitializeOld(void)
{
    ubyte   *image_data;
    int	    image_height, image_width;

    // GROUND
	// Load the image for the texture. The texture file has to be in
    // a place where it will be found.
    if ( ! ( image_data = (ubyte*)tga_load("terrain3.tga", &image_width,
					   &image_height, TGA_TRUECOLOR_24) ) )
    {
	fprintf(stderr, "Ground::Initialize: Couldn't load terrain3.tga\n");
	return false;
    }

    // This creates a texture object and binds it, so the next few operations
    // apply to this texture.
    glGenTextures(1, &groundTexture);
    glBindTexture(GL_TEXTURE_2D, groundTexture);

	// This sets a parameter for how the texture is loaded and interpreted.
	// basically, it says that the data is packed tightly in the image array.
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

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

	// This says what to do with the texture. Modulate will multiply the
	// texture by the underlying color.
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 

	// Now do the geometry. Create the display list.
	display_list = glGenLists(1);
	glNewList(display_list, GL_COMPILE);
	// Use white, because the texture supplies the color.
	glColor3f(1.0, 1.0, 1.0);

	// The surface normal is up for the ground.
	// Well not really.
	glNormal3f(0.0, 0.0, 1.0);

	// Turn on texturing and bind the grass texture.
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, groundTexture);

	if (true) {
		// Draw the ground as triangle strips, specifying texture coordinates.
		// Note that every other texture mapping is upside down.
		// This is due to sharing of two vertices (and hence texture coordinates)
		// between successive triangles in the strip.
		GLfloat h1, h2, h3, h4;
		int vstride = 4;
		int tstride = m_heightmap_width * vstride / (int)m_parkWidth; // Assuming all is square

		for (int y = -(int)m_parkLength/2, j = 0;y < (int)m_parkLength/2; y+=vstride, j += tstride) {
			glBegin(GL_TRIANGLE_STRIP);
			// Make first two vertices of first triangle in strip
			
			// (0,y+1)
			h1 = GetHeight(0, y+m_parkLength/2+vstride);
			glTexCoord2f(0, (float)(j+tstride)/m_heightmap_height);
			glNormal3f(0.0, 0.0, 1.0);
			glVertex3f(-m_parkWidth/2, (GLfloat)(y+vstride), h1);

			// (0,y)
			h2 = GetHeight(0, y+m_parkLength/2);
			glTexCoord2f(0, (float)(j)/m_heightmap_height);
			glNormal3f(0.0, 0.0, 1.0);
			glVertex3f(-m_parkWidth/2, (GLfloat)y, h2);

			for (int x = -(int)m_parkWidth/2, i = 0;x < (int)m_parkWidth/2; x+=vstride, i += tstride) {
				// Now complete a triangle with each additional vertex

				// (x+1,y+1)
				h3 = GetHeight(x+m_parkWidth/2+vstride, y+m_parkLength/2+vstride);
				if (abs(h1-h3) < 2) {
					glTexCoord2f((float)(i+tstride)/m_heightmap_width, (float)(j+tstride)/m_heightmap_height);
				}
				else {
					glTexCoord2f((float)(i+tstride)/m_heightmap_width, (float)(j+tstride)/m_heightmap_height);
				}
				glNormal3f(0.0, 0.0, 1.0);
				glVertex3f((float)(x+vstride), (float)(y+vstride), h3);

				// (x+1,y)
				h4 = GetHeight(x+m_parkWidth/2+vstride, y+m_parkLength/2);
				if (abs(h1-h4) < 2) {
					glTexCoord2f((float)(i+tstride)/m_heightmap_width, (float)(j)/m_heightmap_height);
				}
				else {
					glTexCoord2f((float)(i+tstride)/m_heightmap_width, (float)(j)/m_heightmap_height);
				}
				glNormal3f(0.0, 0.0, 1.0);
				glVertex3f((float)(x+vstride), (float)y, h4);

				h1 = h3;
				h2 = h4;
				//break;
			}
			glEnd();
		}
	}
	else {
		// For repeated textures, the range is 0 to 1 for every repeat of the texture,
		// as is 1 to 2, 2 to 3, and even -1 to 0. So -1 to 1 will repeat twice in
		// each direction for 4 total replications.  Original code used -100 to 100
		// for 40k reps.
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex3f(64, 64, 0.0);
		glTexCoord2f(0, 1);
		glVertex3f(-64, 64, 0.0);
		glTexCoord2f(0, 0);
		glVertex3f(-64, -64, 0.0);
		glTexCoord2f(1, 0);
		glVertex3f(64, -64, 0.0);
		glEnd();
	}

	// Turn texturing off again, because we don't want everything else to
	// be textured.
	glDisable(GL_TEXTURE_2D);
    glEndList();

    // We only do all this stuff once, when the GL context is first set up.
    initialized = true;

    return true;
}

// Draw just calls the display list we set up earlier.
void
Ground::Draw(void)
{
    glPushMatrix();
    glCallList(display_list);
    glPopMatrix();
}

/*
// Code from Project 1 (TargaImage.cpp)
// Used to make terrain texture matching elevation map
// Project 1 commands to recreate:
//	load heightmap2.tga
//	make-height-map snow1.tga stone1.tga grass1.tga sand1.tga
//	save terrain2.tga
//
bool Ground::MakeHeightMap(TargaImage* pImage0, TargaImage* pImage1, TargaImage* pImage2, TargaImage* pImage3)
{
	float tex_fact[5];  //Percentage of visibility for each texture
	float h;  //The height at pos (x/y)
	//bitmap final_tex;   //The final texture to be returned
	//The new rgb values to be written
	unsigned char new_r, new_g, new_b;  //All textures rgb values at pos (x/y)

	int i, j;
	unsigned char *pixel; // rgba for current pixel
	unsigned char *pixel0; // rgba for current pixel
	unsigned char *pixel1; // rgba for current pixel
	unsigned char *pixel2; // rgba for current pixel
	unsigned char *pixel3; // rgba for current pixel
	unsigned char *pixel4; // rgba for current pixel
	unsigned char I; // intensity value for current pixel

	if (! data)
		return false;
	if (! pImage0)
		return false;
	if (! pImage1)
		return false;
	if (! pImage2)
		return false;
	if (! pImage3)
		return false;

	//Go through a map of 256x256
	for (int y=0; y<1024; y++) {
		int offset = y * width * 4;
		for (int x=0; x<1024; x++) {
			//Get height at pos (x/y) out of bitmap
			pixel = data + (offset + x*4);
			h = floor((0.299f * (float)pixel[0] + 0.587f * (float)pixel[1] + 0.114f * (float)pixel[2]));

			//for (int k = 0;k<127;k++) {
			//	cout << texfactor(64, k) << "\n";
			//}
			//for (int k = 0;k<127;k++) {
			//	cout << texfactor(128, k) << "\n";
			//}
			//for (int k = 0;k<127;k++) {
			//	cout << texfactor(192, k) << "\n";
			//}
			//for (int k = 0;k<127;k++) {
			//	cout << texfactor(64, k) << "\n";
			//}
			//Get percentage for all bitmaps(Regions)
			tex_fact[0]=texfactor(256, h);
			tex_fact[1]=texfactor(192, h);
			tex_fact[2]=texfactor(128, h);
			tex_fact[3]=texfactor(64, h);
			tex_fact[4]=texfactor( 0, h);
			//Read all texture rgb values
			pixel0 = pImage0->data + (offset + x*4);
			pixel1 = pImage1->data + (offset + x*4);
			pixel2 = pImage2->data + (offset + x*4);
			pixel3 = pImage3->data + (offset + x*4);
			pixel4 = pImage3->data + (offset + x*4); // not a typo
			
			//Compose new rgb values for final texture
			new_r=((tex_fact[0]*pixel0[0]) + 
				   (tex_fact[1]*pixel1[0]) + 
				   (tex_fact[2]*pixel2[0]) + 
				   (tex_fact[3]*pixel3[0]) + 
				   (tex_fact[4]*pixel3[0]));
			new_g=((tex_fact[0]*pixel0[1]) + 
				   (tex_fact[1]*pixel1[1]) + 
				   (tex_fact[2]*pixel2[1]) + 
				   (tex_fact[3]*pixel3[1]) + 
				   (tex_fact[4]*pixel3[1]));
			new_b=((tex_fact[0]*pixel0[2]) + 
				   (tex_fact[1]*pixel1[2]) + 
				   (tex_fact[2]*pixel2[2]) + 
				   (tex_fact[3]*pixel3[2]) + 
				   (tex_fact[4]*pixel3[2]));
			//Write new color to texture
			if (new_r >= 255) {
				cout << "red max out." << endl;
			}
			if (new_g >= 255) {
				cout << "green max out." << endl;
			}
			if (new_b >= 255) {
				cout << "blue max out." << endl;
			}
			pixel[RED] = new_r;
			pixel[GREEN] = new_g;
			pixel[BLUE] = new_b;
		}
	}

	// place black border around map
	// makes nice map edges when viewed from side
	for (int y=0; y<1024; y++) {
		int offset = y * width * 4;
		pixel = data + (offset);
		pixel[RED] = 0;
		pixel[GREEN] = 0;
		pixel[BLUE] = 0;
	}
	for (int y=0; y<1024; y++) {
		int offset = y * width * 4;
		pixel = data + (offset + 1023*4);
		pixel[RED] = 0;
		pixel[GREEN] = 0;
		pixel[BLUE] = 0;
	}
	for (int x=0; x<1024; x++) {
		int offset = 0;
		pixel = data + (offset + x*4);
		pixel[RED] = 0;
		pixel[GREEN] = 0;
		pixel[BLUE] = 0;
	}
	for (int x=0; x<1024; x++) {
		int offset = 1023 * width * 4;
		pixel = data + (offset + x*4);
		pixel[RED] = 0;
		pixel[GREEN] = 0;
		pixel[BLUE] = 0;
	}

	return true;
}
float Ground::texfactor(float h1, float h2)
{
  float percent;
  percent = (64.0f - abs(h1 - h2)) / 64.0f;
 
  if(percent < 0.0f) percent = 0.0f;
  else if(percent > 1.0f) percent = 1.0f;  return percent;
}
*/
