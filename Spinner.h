#ifndef _SPINNER_H_
#define _SPINNER_H_

#include <Fl/gl.h>
#include <gl/glu.h>
#include "libtarga.h"
#include "ProjUtils.h"
#include "SurfRev.h"
#include <list>
#include <vector>

class Spinner {
public:
	// Constructor
	Spinner(GLfloat x, GLfloat y, GLfloat z);

	// Destructor
	~Spinner(void);

	GLUquadricObj *quadratic;
	void Initialize();
	void ReInitialize();
	void Draw();
	SurfRev* m_pBase;
	GLubyte dlSpinner;
	void Update(float dt, int numFrames);
	GLfloat			w; // angular position of carriage
	GLfloat			speed; // The Ferris Wheel's speed, in revs per update
	GLfloat			m_theta; // angle of the center of rotation of ferris wheel,
						// relative to x-axis
	GLfloat			m_phi; // angle of carriage swing from horizontal
	GLfloat m_zeta0; // angle of lever arm
	GLfloat m_zeta1; // angle of lever arm
	GLfloat m_zeta2; // angle of lever arm
	GLfloat m_zeta3; // angle of lever arm
	GLfloat m_baseradius;
	GLfloat m_x;
	GLfloat m_y;
	GLfloat m_z;

private:
};

#endif // _SPINNER_H_