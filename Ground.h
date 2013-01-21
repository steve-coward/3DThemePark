/*
 * Ground.h: Header file for a class that draws the ground.
 *
 * (c) 2001-2002: Stephen Chenney, University of Wisconsin at Madison.
 */


#ifndef _GROUND_H_
#define _GROUND_H_

#include <Fl/gl.h>
#include "libtarga.h"

class Ground {
  private:
    GLubyte display_list;   // The display list that does all the work.
    GLuint  groundTexture;    // The object for the grass texture.
    GLuint  cliffTexture;    // The object for the cliff texture.
    bool    initialized;    // Whether or not we have been initialised.

	//float texfactor(float h1, float h2);
	//bool MakeHeightMap(TargaImage* pImage0, TargaImage* pImage1, TargaImage* pImage2, TargaImage* pImage3);
public:
	bool m_bUseHeightMap;
	GLfloat m_parkWidth;
	GLfloat m_parkLength;
	ubyte* m_heightmap;
    int	m_heightmap_height;
	int	m_heightmap_width;
	GLfloat m_heightscale; // > 0 reduces height

	GLfloat GetHeight(GLfloat x, GLfloat y);


  public:
    // Constructor. Can't do initialization here because we are
    // created before the OpenGL context is set up.
    Ground() { 
		display_list = 0;
		initialized = false;
		m_heightscale = 4.0f; // > 0 reduces height
	};

    // Destructor. Frees the display lists and texture object.
    ~Ground(void);

    // Initializer. Creates the display list.
    bool    Initialize(void);
	bool    InitializeOld(void);

    // Does the drawing.
    void    Draw(void);
};


#endif
