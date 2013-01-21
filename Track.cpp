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
* Track.cpp: A class that draws the train and its track.
*
* (c) 2001-2002: Stephen Chenney, University of Wisconsin at Madison.
*/


#include "Track.h"
#include "ProjUtils.h"
#include <stdio.h>
#include <FL/math.h>
#include <gl/glu.h>
#include <list>

// The control points for the track spline.
const int   Track::TRACK_NUM_CONTROLS = 4;

// The carriage energy and mass
const float Track::TRAIN_ENERGY = 250.0f;

Track::Track(GLfloat cx, GLfloat cy, GLfloat width, GLfloat length, Ground* pGround)
{
	initialized = false;
	m_pGround = pGround;
	track_width = 0.8f;
	m_cx = cx;
	m_cy = cy;
	m_cz = m_pGround->GetHeight(m_cx+m_pGround->m_parkWidth/2, m_cy+m_pGround->m_parkLength/2);
	m_width = width;
	m_length = length;
	car_size = 0.5f; // Actually half the car dimension
};

// Destructor
Track::~Track(void)
{
    if ( initialized )
    {
		glDeleteLists(track_list, 1);
		glDeleteLists(train_list, 1);
    }
}



// Initializer. Would return false if anything could go wrong.
bool Track::Initialize(void)
{
	std::list<track_spline_params*>::iterator itr;
    float p[3];
    float lp[3];
	float lastheight;
	float radial[3];
	float thisheight;
    int i;
	ubyte *image_data;
    int image_height, image_width;

    // Load the image for the texture.
    if ( ! ( image_data = (ubyte*)tga_load("wood.tga", &image_width,
					   &image_height, TGA_TRUECOLOR_24) ) )
    {
		fprintf(stderr, "Track::Initialize: Couldn't load wood.tga\n");
		return false;
    }

	// This sets a parameter for how the texture is loaded and interpreted.
    // basically, it says that the data is packed tightly in the image array.
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	// This creates a texture object and binds it, so the next few operations
    // apply to this texture.
	glGenTextures(1, &texRoller);
    glBindTexture(GL_TEXTURE_2D, texRoller);

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
	
	quadratic=gluNewQuadric(); // Create A Pointer To The Quadric Object
	gluQuadricNormals(quadratic, GLU_SMOOTH); // Create Smooth Normals ( NEW )
	gluQuadricTexture(quadratic, GL_TRUE); // Create Texture Coords ( NEW )

	// Create the display list for the track - just a set of line segments
	// We just use curve evaluated at integer paramer values, because the
	// subdivision has made sure that these are good enough.
	track_list = glGenLists(1);
	glNewList(track_list, GL_COMPILE);
	glBindTexture(GL_TEXTURE_2D, texRoller);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Create the track splines - inner and outer.
	// Inner track will be at front of list.
	listSplineParams.push_back(new track_spline_params());
	listSplineParams.push_back(new track_spline_params());
	float offset = track_width;
	itr = listSplineParams.begin();
	while (itr != listSplineParams.end()) {
		(*itr)->refined = new CubicBspline(3, true);

		(*itr)->track = new CubicBspline(3, true);

		(*itr)->track->z = m_cz;
		(*itr)->refined->z = m_cz;
		(*itr)->track_controls[0][0] = m_cx - m_width/2 + offset;
		(*itr)->track_controls[0][1] = m_cy - m_length/2 + offset;
		(*itr)->track_controls[0][2] = -18;
		(*itr)->track_controls[1][0] = m_cx + m_width/2 - offset;
		(*itr)->track_controls[1][1] = m_cy - m_length/2 + offset;
		(*itr)->track_controls[1][2] = 40;
		(*itr)->track_controls[2][0] = m_cx + m_width/2 - offset;
		(*itr)->track_controls[2][1] = m_cy + m_length/2 - offset;
		(*itr)->track_controls[2][2] = -18;
		(*itr)->track_controls[3][0] = m_cx - m_width/2 + offset;
		(*itr)->track_controls[3][1] = m_cy + m_length/2 - offset;
		(*itr)->track_controls[3][2] = 40;

		for ( i = 0 ; i < TRACK_NUM_CONTROLS ; i++ ) {
			(*itr)->track->Append_Control((*itr)->track_controls[i]);
		}

		// Refine it down to a fixed tolerance. This means that any point on
		// the track that is drawn will be less than 0.1 units from its true
		// location. In fact, it's even closer than that.
		(*itr)->track->Refine_Tolerance(*(*itr)->refined, 0.1f);
		(*itr)->n_refined = (*itr)->refined->N();

		glColor3f(1.0f, 1.0, 1.0f);
		glBegin(GL_LINE_STRIP);
		for ( i = 0 ; i <= (*itr)->n_refined ; i++ )
		{
			(*itr)->refined->Get_Point((float)i, p);
			glVertex3fv(p);
		}
		glEnd();

		// Create roller coaster support structure
		// Direction of creation of structure is counter clockwise as seen from above.
		// glRotate follows the right-hand rule, so if the vector (x, y, z) points toward
		// the user, the rotation will be counter clockwise. 
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();

		// Loop initialization.
		int start = 0;
		(*itr)->refined->Get_Point((float)start, p);
		thisheight = m_pGround->GetHeight(p[0]+m_pGround->m_parkWidth/2, p[1]+m_pGround->m_parkLength/2);
		glTranslatef(p[0], p[1], 0);

		// Now iterate through poles.
		// Keep vertex count down by skipping a few poles.
		// If it matters - the first pole drawn will be one of the tallest 
		// poles in structure (for the current spline.)
		//
		// Each iteration draws 1 vertical pole, 1 horizontal pole, 2 diagonals
		for ( i = start+4 ; i <= (*itr)->n_refined ; i+=4 )
		{
			// Vertical pole, height = p[2]-thisheight
			glPushMatrix();
			glTranslatef(0, 0, thisheight);
			gluCylinder(quadratic, 0.2f, 0.2f, p[2]-thisheight, 8, 1);
			glPopMatrix();

			// Remember current location so we can tie into it from next pole.
			lp[0] = p[0];
			lp[1] = p[1];
			lp[2] = p[2];
			lastheight = thisheight;

			(*itr)->refined->Get_Point((float)i, p);
			thisheight = m_pGround->GetHeight(p[0]+m_pGround->m_parkWidth/2, p[1]+m_pGround->m_parkLength/2);

			// This points towards interior of spline (RHS).
			// This is <0,0,1>x<px-lpx,py-lpy,pz-lpz>
			radial[0] = p[1]-lp[1];
			radial[1] = lp[0]-p[0];
			radial[2] = 0;

			// Diagonal distance from top of pole being placed to base of previous pole.
			float dd;
			// Angle of rotation of diagonal pole.
			float aa;

			if ((p[2]) > (lp[2])) {
				dd = sqrt((lp[2]-lastheight)*(lp[2]-lastheight) + (p[0]-lp[0])*(p[0]-lp[0]) + (p[1]-lp[1])*(p[1]-lp[1]));
				aa = atan(sqrt((p[0]-lp[0])*(p[0]-lp[0]) + (p[1]-lp[1])*(p[1]-lp[1]))/(lp[2]-lastheight)) * 360.0f/TwoPi;
			}
			else {
				dd = sqrt((p[2]-lastheight)*(p[2]-lastheight) + (p[0]-lp[0])*(p[0]-lp[0]) + (p[1]-lp[1])*(p[1]-lp[1]));
				aa = atan(sqrt((p[0]-lp[0])*(p[0]-lp[0]) + (p[1]-lp[1])*(p[1]-lp[1]))/(p[2]-lastheight)) * 360.0f/TwoPi;
			}

			// Diagonal pole - from base of pole just built to top of previous pole.
			// Prevent ground from obscuring diagonals for short vertical poles
			if (lp[2]-lastheight > 2) {
				glPushMatrix();
				glTranslatef(0, 0, lastheight);
				glRotatef(aa, -radial[0], -radial[1], -radial[2]);
				gluCylinder(quadratic, 0.2f, 0.2f, dd, 8, 1);
				gluQuadricOrientation(quadratic,GLU_INSIDE);
				//draw the first cap
				gluDisk( quadratic, 0.0, 0.2f, 16, 1);
				glTranslatef( 0,0,dd );
				//draw the second cap
				gluQuadricOrientation(quadratic,GLU_OUTSIDE);
				gluDisk( quadratic, 0.0, 0.2f, 16, 1);
				glPopMatrix();
			}

			// Horizontal pole.
			float ddd = sqrt((p[0]-lp[0])*(p[0]-lp[0]) + (p[1]-lp[1])*(p[1]-lp[1]));
			glPushMatrix();
			if ((p[2]) > (lp[2])) {
				glTranslatef(0, 0, lp[2]);
			}
			else {
				glTranslatef(0, 0, p[2]);
			}
			glRotatef(-90, radial[0], radial[1], radial[2]);
			gluCylinder(quadratic, 0.2f, 0.2f, ddd, 8, 1);
			gluQuadricOrientation(quadratic,GLU_INSIDE);
			//draw the first cap
			gluDisk( quadratic, 0.0, 0.2f, 16, 1);
			glTranslatef( 0,0,ddd );
			//draw the second cap
			gluQuadricOrientation(quadratic,GLU_OUTSIDE);
			gluDisk( quadratic, 0.0, 0.2f, 16, 1);

			glPopMatrix();
			

			if ((p[2]) > (lp[2])) {
				dd = sqrt((lp[2]-thisheight)*(lp[2]-thisheight) + (p[0]-lp[0])*(p[0]-lp[0]) + (p[1]-lp[1])*(p[1]-lp[1]));
				aa = atan(sqrt((p[0]-lp[0])*(p[0]-lp[0]) + (p[1]-lp[1])*(p[1]-lp[1]))/(lp[2]-thisheight)) * 360.0f/TwoPi;
			}
			else {
				dd = sqrt((p[2]-thisheight)*(p[2]-thisheight) + (p[0]-lp[0])*(p[0]-lp[0]) + (p[1]-lp[1])*(p[1]-lp[1]));
				aa = atan(sqrt((p[0]-lp[0])*(p[0]-lp[0]) + (p[1]-lp[1])*(p[1]-lp[1]))/(p[2]-thisheight)) * 360.0f/TwoPi;
			}

			// Diagonal pole - from top of pole just built to base of previous pole.
			glTranslatef((p[0]-lp[0]), (p[1]-lp[1]), 0);
			// Prevent ground from obscuring diagonals for short vertical poles
			if (p[2]-thisheight > 2) {
				glPushMatrix();
				glTranslatef(0, 0, thisheight);
				glRotatef(aa, radial[0], radial[1], radial[2]);
				gluCylinder(quadratic, 0.2f, 0.2f, dd, 8, 1);
				gluQuadricOrientation(quadratic,GLU_INSIDE);
				//draw the first cap
				gluDisk( quadratic, 0.0, 0.2f, 16, 1);
				glTranslatef( 0,0,ddd );
				//draw the second cap
				gluQuadricOrientation(quadratic,GLU_OUTSIDE);
				gluDisk( quadratic, 0.0, 0.2f, 16, 1);
				glPopMatrix();
			}
		}
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		offset = 0; // outer track will be larger (no offset)
		++itr;
	}
	glEndList();

	// car at the front of vec_cars is the last car in the train of cars
	car* c;
	GLfloat color[3] = { 1.0, 0.0, 0.0 };
	for (int i = 0; i< 16; i++) {
		c = new car();
		c->pos = (float)i/36; // 36 is experimentally determined value
		// to keep cars properly close to each other.
		c->speed = 0.0f;
		c->color[0] = color[0];
		c->color[1] = color[1];
		c->color[2] = color[2];
		color[0] -= 0.00;
		color[1] += 0.06;
		color[2] += 0.06;
		vec_cars.push_back(c);
	}
	
	// Set up the train. At this point a cube is drawn. NOTE: The
    // x-axis will be aligned to point along the track. The origin of the
    // train is assumed to be at the bottom of the train.
    train_list = glGenLists(1);
    glNewList(train_list, GL_COMPILE);
    //glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(car_size, car_size, 1.0f);
	glVertex3f(-car_size, car_size, 1.0f);
	glVertex3f(-car_size, -car_size, 1.0f);
	glVertex3f(car_size, -car_size, 1.0f);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(car_size, -car_size, 0.0f);
	glVertex3f(-car_size, -car_size, 0.0f);
	glVertex3f(-car_size, car_size, 0.0f);
	glVertex3f(car_size, car_size, 0.0f);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(car_size, car_size, 0.0f);
	glVertex3f(car_size, car_size, 1.0f);
	glVertex3f(car_size, -car_size, 1.0f);
	glVertex3f(car_size, -car_size, 0.0f);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-car_size, car_size, 1.0f);
	glVertex3f(-car_size, car_size, 0.0f);
	glVertex3f(-car_size, -car_size, 0.0f);
	glVertex3f(-car_size, -car_size, 1.0f);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(car_size, car_size, 1.0f);
	glVertex3f(car_size, car_size, 0.0f);
	glVertex3f(-car_size, car_size, 0.0f);
	glVertex3f(-car_size, car_size, 1.0f);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(car_size, -car_size, 0.0f);
	glVertex3f(car_size, -car_size, 1.0f);
	glVertex3f(-car_size, -car_size, 1.0f);
	glVertex3f(-car_size, -car_size, 0.0f);
    glEnd();
    glEndList();

    initialized = true;

    //glDisable(GL_TEXTURE_2D);

	return true;
}


// Draw
void Track::Draw(void)
{
    float   posn[3];
    float   tangent[3];
	float   radial[3];
    double  angle;
	std::vector<car*>::iterator itr;

    if ( ! initialized )
	return;

    glPushMatrix();

    // Draw the track
    glCallList(track_list);

	itr = vec_cars.begin();

	while (itr != vec_cars.end()) {
		glPushMatrix();

		// Figure out where the train is
		listSplineParams.front()->track->Get_Point((*itr)->pos, posn);
		radial[0] = posn[0] - m_cx;
		radial[1] = posn[1] - m_cy;
		radial[2] = 0;
		Normalize_3(radial);
		radial[0] *= track_width/2;
		radial[1] *= track_width/2;

		// Translate the train to the point
		glTranslatef(posn[0], posn[1], posn[2]);

		// Now center the train on the double track
		// Without this train rides centered on inner track
		// Move radially outward half width.
		glTranslatef(radial[0], radial[1], radial[2]);

		// ...and what it's orientation is
		listSplineParams.front()->track->Evaluate_Derivative((*itr)->pos, tangent);
		Normalize_3(tangent);

		// Rotate it to point along the track, but stay horizontal
		angle = atan2(tangent[1], tangent[0]) * 360.0f/TwoPi;
		glRotatef((float)angle, 0.0f, 0.0f, 1.0f);

		// Another rotation to get the tilt right.
		angle = asin(-tangent[2]) * 360.0f/TwoPi;
		glRotatef((float)angle, 0.0f, 1.0f, 0.0f);

		glColor3fv((*itr)->color);
		
		// Draw the train
		glCallList(train_list);
		

		glPopMatrix();
		++itr;
	}
    glPopMatrix();
}


void
Track::Update(float dt)
{
	float   point[3];
	float   deriv[3];
	double  length;
	double  parametric_speed;
	std::vector<car*>::iterator itr;

	if ( ! initialized )
		return;

	itr = vec_cars.begin();

	while (itr != vec_cars.end()) {
		// First we move the train along the track with its current speed.

		// Get the derivative at the current location on the track.
		listSplineParams.front()->track->Evaluate_Derivative((*itr)->pos, deriv);

		// Get its length.
		length = sqrt(deriv[0]*deriv[0] + deriv[1]*deriv[1] + deriv[2]*deriv[2]);
		if ( length == 0.0 )
			return;

		// The parametric speed is the world train speed divided by the length
		// of the tangent vector.
		parametric_speed = (*itr)->speed / length;

		// Now just evaluate dist = speed * time, for the parameter.
		(*itr)->pos += (float)(parametric_speed * dt);

		// If we've just gone around the track, reset back to the start.
		if ( (*itr)->pos > listSplineParams.front()->refined->N() ) {
			(*itr)->pos -= listSplineParams.front()->refined->N();
		}

		// As the second step, we use conservation of energy to set the speed
		// for the next time.
		// The total energy = z * gravity + 1/2 speed * speed, assuming unit mass
		listSplineParams.front()->track->Evaluate_Point((*itr)->pos, point);
		if ( TRAIN_ENERGY - 9.81 * point[2] < 0.0 )
			(*itr)->speed = 0.0;
		else
			(*itr)->speed = (float)sqrt(2.0 * ( TRAIN_ENERGY - 9.81 * point[2] ));
		++itr;
	}
}


