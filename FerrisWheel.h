/*
 * FerrisWheel.h: Header file for a class that draws the Ferris Wheel.
 *
 * (c) 2001: Stephen Chenney, University of Wisconsin at Madison.
 */


#ifndef _FERRISWHEEL_H_
#define _FERRISWHEEL_H_

#include <Fl/gl.h>
#include <gl/glu.h>

class FerrisWheel {
  private:
	GLfloat			halfwidth; // half the distance separating two hoops
	GLfloat			offset; // distance from carriage to ground at bottom
	GLUquadricObj	*quadratic;
	GLfloat			m_pos[3]; // coordinates of center of ferris wheel
	GLfloat			m_radius;
	GLfloat			w; // angular position of carriage
	GLfloat			speed; // The Ferris Wheel's speed, in revs per update
	GLfloat			m_theta; // angle of the center of rotation of ferris wheel,
						// relative to x-axis
	GLfloat			m_phi; // angle of carriage swing from horizontal

    GLuint texFerrisWheel;    // The object for the Ferris Wheel texture.
	GLubyte 	    dlSupport;	    // The display list for the stationary support Ferris Wheel.
	GLubyte 	    dlWheel;	    // The display list for the rotating Ferris Wheel.
    GLubyte 	    dlCarriage;	    // The display list for the Ferris Wheel carriage.
    bool    	    initialized;    // Whether or not we have been initialized.
    
	static const float 	FERRISWHEEL_ENERGY;

  public:
    // Constructor
    FerrisWheel(GLfloat x, GLfloat y, GLfloat z, GLfloat orient, GLfloat radius);

    // Destructor
    ~FerrisWheel(void);

    bool Initialize(void);// Gets everything set up for drawing.
    void Update(float dt, int numFrames);	// Updates the location of the train
    void Draw(void); // Draws everything.
	void DrawTorus(float majorRadius, float minorRadius, int numMajor, int numMinor);
	void ReduceToUnit(float vector[3]); // Reduces A Normal Vector (3 Coordinates)
};


#endif // _FERRISWHEEL_H_

