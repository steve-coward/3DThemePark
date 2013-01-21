/*
 * Track.h: Header file for a class that draws the train and its track.
 *
 * (c) 2001: Stephen Chenney, University of Wisconsin at Madison.
 */


#ifndef _TRAINTRACK_H_
#define _TRAINTRACK_H_

#include <Fl/gl.h>
#include <gl/glu.h>
#include "CubicBspline.h"
#include "libtarga.h"
#include "Ground.h"
#include <list>
#include <vector>

struct track_spline_params {
	float track_controls[4][3]; // geometry of elliptic spline
	CubicBspline* track;
	CubicBspline* refined;
	int n_refined;
};

struct car {
	float pos; // The train's parametric position on the track.
	float speed; // The train's speed, in world coordinates
	GLfloat color[3];
};

class Track {
  private:
	Ground* m_pGround;
    GLubyte 	    track_list;	    // The display list for the track.
    GLubyte 	    train_list;	    // The display list for the train.
    bool    	    initialized;    // Whether or not we have been initialized.
public:
	std::list<track_spline_params*> listSplineParams;
	std::vector<car*> vec_cars;
private:
    static const int	TRACK_NUM_CONTROLS;	// Constants about the track.
    static const float 	TRAIN_ENERGY;

	GLUquadricObj *quadratic;
	GLuint texRoller;    // The object for the Roller Coaster texture.
	float m_width;
	float m_length;
	float m_cx;
	float m_cy;
	float m_cz;
	float track_width;
public:
	float car_size;

  public:
    // Constructor
    Track(GLfloat cx, GLfloat cy, GLfloat width, GLfloat length, Ground* pGround);

    // Destructor
    ~Track(void);

    bool    Initialize(void);	// Gets everything set up for drawing.
    void    Update(float);	// Updates the location of the train
    void    Draw(void);		// Draws everything.
};


#endif

