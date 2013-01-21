/*
 * Bridge.h: Header file for a class that draws the train and its track.
 *
 * (c) 2001: Stephen Chenney, University of Wisconsin at Madison.
 */


#ifndef _BRIDGE_H_
#define _BRIDGE_H_

#include <Fl/gl.h>
#include <gl/glu.h>
#include "libtarga.h"
#include "Bridge.h"
#include "Ground.h"
#include <list>
#include <vector>

class Bridge {
  private:
	Ground* m_pGround;
    GLubyte bridge_list; // The display list for the track.
    bool initialized; // Whether or not we have been initialized.
private:
	GLuint texBridge; // The object for the Roller Coaster texture.
	float m_width;
	float m_length;
	float m_cx;
	float m_cy;
	float m_cz;
	float m_radius;
public:
    // Constructor
    Bridge(GLfloat cx, GLfloat cy, GLfloat width, GLfloat length, GLfloat radius, Ground* pGround);

    // Destructor
    ~Bridge(void);

    bool Initialize(void); // Gets everything set up for drawing.
    void Update(float); // Updates the location of the train
    void Draw(void); // Draws everything.
};


#endif  // _BRIDGE_H_

