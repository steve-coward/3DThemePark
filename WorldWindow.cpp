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
*/

#include "WorldWindow.h"
#include "ProjUtils.h"
#include <Fl/math.h>
#include <Fl/gl.h>
#include <GL/glu.h>
#include <fl/glut.h>
#include "libtarga.h"
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <time.h>

const double WorldWindow::FOV_X = 45.0;

WorldWindow::WorldWindow(int x, int y, int width, int height, char *label)
: Fl_Gl_Window(x, y, width, height, label)
{
	button = -1;
	m_bPause = false;
	m_bUseHeightMap = true;
	m_bPrintHelp = true;
	m_font = GLUT_BITMAP_HELVETICA_12;
	m_parkWidth = (GLfloat)x;
	m_parkLength = (GLfloat)y;
	m_windowWidth = width;
	m_windowHeight = height;
	m_numSubDivides = 0;

	// Initial viewing parameters.
	useNewNav = 0;
}

void WorldWindow::init(void)
{
	unsigned int t;
	t = time(NULL);
	t = 1299639575;
	std::cout << "seed = " << t << "\n";
	srand ( t );

	// Load height map
	// Load the image for the texture. The texture file has to be in
	// a place where it will be found.
	if ( ! ( m_heightmap = (ubyte*)tga_load("heightmap3.tga", &m_heightmap_width,
		&m_heightmap_height, TGA_TRUECOLOR_24) ) )
	{
		fprintf(stderr, "Ground::Initialize: Couldn't load heightmap1.tga\n");
		return;
	}

	m_pGround = new Ground();

	m_pGround->m_bUseHeightMap = m_bUseHeightMap;
	m_pGround->m_heightmap = m_heightmap;
	m_pGround->m_heightmap_width = m_heightmap_width;
	m_pGround->m_heightmap_height = m_heightmap_height;
	m_pGround->m_parkLength = m_parkLength;
	m_pGround->m_parkWidth = m_parkWidth;

	// Increasing x moves object due east.
	// Increasing y moves object due north.
	m_pBridge1 = new Bridge(120, 80, 5, 32, 8, m_pGround);
	m_pBridge2 = new Bridge(120, 80, 5, 32, 8, m_pGround);

	m_pRollerCoaster = new Track(81, -36, 40, 80, m_pGround);

	m_pFerrisWheel = new FerrisWheel(40, 59, m_pGround->GetHeight(40+m_parkWidth/2, 59+m_parkLength/2), 0, 10);

	m_pFence = new Fence();

	m_pSpinner = new Spinner(15, -10, m_pGround->GetHeight(15+m_parkWidth/2, -10+m_parkLength/2) );
	
	Tree* tree;
	for (int kk=0;kk<12;kk++) {
		// randomly spread thru park
		//float x = -m_parkWidth/2 + (float)(rand() % (int)m_parkWidth);
		//float y = -m_parkLength/2 + (float)(rand() % (int)m_parkLength);
		
		// on slope by coaster
		float x =  82-20 + (float)(rand() % 40);
		float y = -40-40 + (float)(rand() % 60);
		float h = m_pGround->GetHeight(x+m_pGround->m_parkWidth/2, y+m_pGround->m_parkLength/2);
		//std::cout << "Tree at " << x << " " << y << " " << h << "\n";
		tree = new Tree(x, y, h);
		m_listTrees.push_back(tree);
	}

	for (int kk=0;kk<12;kk++) {
		// randomly spread thru park
		//float x = -m_parkWidth/2 + (float)(rand() % (int)m_parkWidth);
		//float y = -m_parkLength/2 + (float)(rand() % (int)m_parkLength);
		
		// on slope by coaster
		float x = -124 + (float)(rand() % 40);
		float y = -124 + (float)(rand() % 60);
		float h = m_pGround->GetHeight(x+m_pGround->m_parkWidth/2, y+m_pGround->m_parkLength/2);
		//std::cout << "Tree at " << x << " " << y << " " << h << "\n";
		tree = new Tree(x, y, h);
		m_listTrees.push_back(tree);
	}

	//m_pSurfRevf = new SurfRev(&Curve2DQuadratic, &Curve2DLinear, 1.0f, 1.0f);
	//std::list<Point2f> listPoints;
	//ShroomOutline(&listPoints);
	//m_pSurfRevl = new SurfRev(listPoints, &Curve2DQuadratic, 1.0f, 1.5f);

	if (useNewNav == 0) {
		// Global viewpoint from above, defined with starting template code
		phi = 45.0f;
		theta = 0.0f;
		dist = 400.0f;
		x_at = 0.0f;
		y_at = 0.0f;
		z_at = 2.0f;
	}
	else if (useNewNav == 1) {
		// First person view from in the park
		phi = 0.0f; // inclination
		theta = 0.0f; // azimuth
		dist = m_parkWidth;
		m_x = 0.0f;
		m_y = 0.0f;
		ubyte* pixel;
		pixel = m_heightmap + (int)m_y * m_heightmap_width * 3 + (int)m_x * 3;
		m_z = 2.0f + (255 - (0.299f * (float)pixel[0] + 0.587f * (float)pixel[1] + 0.114f * (float)pixel[2]))/16;		
	}
	else if ((useNewNav == 2) || (useNewNav == 3)) {
		// On the roller coaster, 2=in last cat, 3=in front car
		phi = 0.0f; // inclination
		theta = 0.0f; // azimuth
		dist = m_parkWidth;
		m_x = 0.0f;
		m_y = 0.0f;
		ubyte* pixel;
		pixel = m_heightmap + (int)m_y * m_heightmap_width * 3 + (int)m_x * 3;
		m_z = 2.0f + (255 - (0.299f * (float)pixel[0] + 0.587f * (float)pixel[1] + 0.114f * (float)pixel[2]))/16;		
	}

	m_numSubDivides = 0;
}

// Destructor
WorldWindow::~WorldWindow(void)
{
	delete m_pGround;
	delete m_pRollerCoaster;
	delete m_pFerrisWheel;
	//delete m_pSurfRevf;
	//delete m_pSurfRevl;
}

void WorldWindow::draw(void)
{
	double  eye[3];
	float   color[4], dir[4];
	GLenum glError;
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
		
	if ( ! valid() )
	{
		// Stuff in here doesn't change from frame to frame, and does not
		// rely on any coordinate system. It only has to be done if the
		// GL context is damaged.
		double	fov_y;

		// Sets the clear color to sky blue.
		glClearColor(0.53f, 0.81f, 0.92f, 1.0);

		// Turn on depth testing
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		// Turn on back face culling. Faces with normals away from the viewer
		// will not be drawn.
		glEnable(GL_CULL_FACE);

		// Enable lighting with one light.
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);

		// Ambient and diffuse lighting track the current color.
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);

		// Turn on normal vector normalization. You don't have to give unit
		// normal vector, and you can scale objects.
		glEnable(GL_NORMALIZE);

		// Set up the viewport.
		glViewport(0, 0, w(), h());

		// Set up the perspective transformation.
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		fov_y = 720.0f / TwoPi * atan(h() * tan(FOV_X * TwoPi / 720.0) / w());
		gluPerspective(fov_y, w() / (float)h(), 1.0, 1000.0);
		glMatrixMode(GL_MODELVIEW);

		// Do some light stuff. Diffuse color, and zero specular color
		// turns off specular lighting.
		color[0] = 1.0f; color[1] = 1.0f; color[2] = 1.0f; color[3] = 1.0f;
		glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
		color[0] = 0.0f; color[1] = 0.0f; color[2] = 0.0f; color[3] = 1.0f;
		glLightfv(GL_LIGHT0, GL_SPECULAR, color);

		// Initialize all the objects.
		m_pGround->Initialize();
		m_pFerrisWheel->Initialize();
		m_pFence->Initialize(false);
		m_pBridge1->Initialize();
		m_pBridge2->Initialize();
		//m_pSurfRevf->Initialize();
		//m_pSurfRevl->Initialize();
		m_pRollerCoaster->Initialize();

		m_pSpinner->Initialize();

		std::list<Tree*>::iterator itr;
		itr = m_listTrees.begin();
		while (itr != m_listTrees.end()) {
			(*itr)->Init();
			++itr;
		}
	}

	// Stuff out here relies on a coordinate system or must be done on every
	// frame.

	// Clear the screen. Color and depth.
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// Set up the viewing transformation.
	if (useNewNav == 0) {
		// The viewer is at a distance
		// dist from (x_at, y_at, z_at) in the direction (theta, phi) defined
		// by two angles. They are looking at (x_at, y_at, z_at) and z is up.
		eye[0] = x_at + dist * cos(theta * TwoPi/360.0f) * cos(phi * TwoPi/360.0f);
		eye[1] = y_at + dist * sin(theta * TwoPi/360.0f) * cos(phi * TwoPi/360.0f);
		eye[2] = z_at + dist * sin(phi * TwoPi/360.0f);
		
		gluLookAt(eye[0], eye[1], eye[2], x_at, y_at, z_at, 0.0, 0.0, 1.0);
	}
	else if (useNewNav == 1) {
		// The viewer is in the center of the park looking North
		// dist from (x_at, y_at, z_at) in the direction (theta, phi) defined
		// by two angles. They are looking at (x_at, y_at, z_at) and z is up.
		eye[0] = m_x;
		eye[1] = m_y;
		eye[2] = m_z;
		x_at = dist * sin(theta * TwoPi/360.0f);
		y_at = dist * cos(theta * TwoPi/360.0f);
		z_at = dist * sin(phi * TwoPi/360.0f);
		
		gluLookAt(eye[0], eye[1], eye[2], x_at, y_at, z_at, 0.0, 0.0, 1.0);
	}
	else if (useNewNav == 2) {
		// On the roller coaster, 2=in last car, 3=in front car		
		float tangenti[3];
		float poso[3];
		float posi[3];
		float up[3];
		float radial[3];
		m_pRollerCoaster->listSplineParams.front()->track->Get_Point(m_pRollerCoaster->vec_cars.front()->pos, posi);
		m_pRollerCoaster->listSplineParams.back()->track->Get_Point(m_pRollerCoaster->vec_cars.front()->pos, poso);
		m_pRollerCoaster->listSplineParams.front()->track->Evaluate_Derivative(m_pRollerCoaster->vec_cars.front()->pos, tangenti);
		Normalize_3(tangenti);
		radial[0] = posi[0] - poso[0];
		radial[1] = posi[1] - poso[1];
		radial[2] = posi[2] - poso[2];
		up[0] = tangenti[1]*radial[2] - tangenti[2]*radial[1];
		up[1] = tangenti[2]*radial[0] - tangenti[0]*radial[2];
		up[2] = tangenti[0]*radial[1] - tangenti[1]*radial[0];
		
		// Move view positin backwards some to avoid artifact of disappearing/reappearing car in front of viewer
		gluLookAt(m_x-3*tangenti[0], m_y-3*tangenti[1], m_z-3*tangenti[2], m_x+tangenti[0], m_y+tangenti[1], m_z+tangenti[2], up[0], up[1], up[2]);
	}
	else if (useNewNav == 3) {
		// On the roller coaster, 2=in last car, 3=in front car
		// Inner track will be at front of listSplineParams list.
		
		float tangenti[3];
		float poso[3];
		float posi[3];
		float up[3];
		float radial[3];
		m_pRollerCoaster->listSplineParams.front()->track->Get_Point(m_pRollerCoaster->vec_cars.back()->pos, posi);
		m_pRollerCoaster->listSplineParams.back()->track->Get_Point(m_pRollerCoaster->vec_cars.back()->pos, poso);
		m_pRollerCoaster->listSplineParams.front()->track->Evaluate_Derivative(m_pRollerCoaster->vec_cars.back()->pos, tangenti);
		Normalize_3(tangenti);
		radial[0] = posi[0] - poso[0];
		radial[1] = posi[1] - poso[1];
		radial[2] = posi[2] - poso[2];
		up[0] = tangenti[1]*radial[2] - tangenti[2]*radial[1];
		up[1] = tangenti[2]*radial[0] - tangenti[0]*radial[2];
		up[2] = tangenti[0]*radial[1] - tangenti[1]*radial[0];
		
		gluLookAt(m_x, m_y, m_z, m_x+tangenti[0], m_y+tangenti[1], m_z+tangenti[2], up[0], up[1], up[2]);
	}
	// Position the light source. This must happen after the viewing
	// transformation is set up, so that the light stays fixed in world
	// space. This is a directional light - note the 0 in the w component.
	dir[0] = 1.0; dir[1] = 1.0; dir[2] = 1.0; dir[3] = 0.0;
	glLightfv(GL_LIGHT0, GL_POSITION, dir);

	// Draw stuff. Everything.
	glPushMatrix();
	m_pGround->Draw();
	m_pRollerCoaster->Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-91,70,m_pGround->GetHeight(-118+m_parkWidth/2,40+m_parkLength/2));
	glRotatef(-55,0,0,1);
	glScalef(0.5, 0.5, 0.5);
	m_pFence->Draw();
	glPopMatrix();

	
	glPushMatrix();
	// elevate the bridge less than 1.0 so that ground covers it where the intersect
	glTranslatef(95, 35, m_pGround->GetHeight(75+m_parkWidth/2,75+m_parkLength/2)-0.1f);
	glRotatef(-72.0f, 0.0f, 0.0f, 1.0f);
	m_pBridge1->Draw();
	glPopMatrix();

	glPushMatrix();
	// elevate the bridge less than 1.0 so that ground covers it where the intersect
	glTranslatef(45, -120, m_pGround->GetHeight(75+m_parkWidth/2,75+m_parkLength/2)-0.2f);
	//glRotatef(-72.0f, 0.0f, 0.0f, 1.0f);
	m_pBridge2->Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-75,15,0);
	glRotatef(35,0,0,1);
	m_pFerrisWheel->Draw();
	glPopMatrix();

	glPushMatrix();
	m_pSpinner->Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8,0,0);
	//m_pSurfRevf->Draw();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-18,0,0);
	//m_pSurfRevl->Draw();
	glPopMatrix();

	glPushMatrix();
	std::list<Tree*>::iterator itr;
	itr = m_listTrees.begin();
	while (itr != m_listTrees.end()) {
		(*itr)->Draw();
		++itr;
	}
	glPopMatrix();

	
	
	// Draw statistic text
	std::string s;
	glDisable(GL_TEXTURE_2D);
	
	// Lightning must be disabled for colored text to work reliably.
	// If there is no light at the text position font will be black.
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f);

	output((int)m_parkWidth/2, 0, "East");
	output((int)-m_parkWidth/2, 0, "West");
	output(0, (int)m_parkLength/2, "North");
	output(0, (int)-m_parkLength/2, "South");

	setOrthographicProjection(); 
	glPushMatrix();
	glLoadIdentity();
	
	if (m_bPrintHelp) {
		s = format("Type 'h' to toggle this display");
		output(5, 10, s.c_str());
		s = format("Type 'v' to cycle views");
		output(5, 22, s.c_str());
		s = format("Type 's' to subdivide base of blue spinning ride");
		output(5, 34, s.c_str());
		s = format("Type 'p' to pause the animation");
		output(5, 46, s.c_str());

		if (useNewNav == 0) {
			s = format("Current view: from above");
			output(5, 58, s.c_str());
			s = format("Left Mouse Left/Right: Rotate park");
			output(5, 70, s.c_str());
			s = format("Left Mouse Up/Down: Tilt park");
			output(5, 82, s.c_str());
			s = format("Both Down: Pan, towards, away");
			output(5, 94, s.c_str());
			s = format("azimuth = %.2f", theta);
			output(5, 106, s.c_str());
			s = format("inclination = %.2f", phi);
			output(5, 118, s.c_str());
			s = format("distance = %.2f", dist);
			output(5, 130, s.c_str());
		}
		else if (useNewNav == 1) {
			s = format("Current view: ground view");
			output(5, 58, s.c_str());
			s = format("Left Mouse Down: rotate azimuth");
			output(5, 70, s.c_str());
			s = format("Right Mouse Down: change inclination");
			output(5, 82, s.c_str());
			s = format("Right Arrow: Move right");
			output(5, 94, s.c_str());
			s = format("Up Arrow: Move forward");
			output(5, 106, s.c_str());
			s = format("Eye(%.2f, %.2f, %.2f)", m_x, m_y, m_z);
			output(5, 118, s.c_str());
			s = format("Look At(%.2f, %.2f, %.2f)", x_at, y_at, z_at);
			output(5, 130, s.c_str());
			s = format("azimuth = %.2f", theta);
			output(5, 142, s.c_str());
			s = format("inclination = %.2f", phi);
			output(5, 154, s.c_str());
			s = format("distance = %.2f", dist);
			output(5, 166, s.c_str());
		}
		else if (useNewNav == 2) {
			s = format("Current view: rear roller coaster car");
			output(5, 58, s.c_str());
		}
		else if (useNewNav == 3) {
			s = format("Current view: front roller coaster car");
			output(5, 58, s.c_str());
		}
	}

	glPopMatrix();
	resetPerspectiveProjection();

	glEnable(GL_LIGHTING);

	glError = GetError(__LINE__, __FILE__);
}


void WorldWindow::setOrthographicProjection() {

	// switch to projection mode
	glMatrixMode(GL_PROJECTION);

	// save previous matrix which contains the 
	//settings for the perspective projection
	glPushMatrix();

	// reset matrix
	glLoadIdentity();

	// set a 2D orthographic projection
	gluOrtho2D(0, m_windowWidth, m_windowHeight, 0);
	
	// switch back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void WorldWindow::resetPerspectiveProjection() {

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}



std::string WorldWindow::format_arg_list(const char *fmt, va_list args)
{
	if (!fmt) return "";
	int   result = -1, length = 256;
	char *buffer = 0;
	while (result == -1)
	{
		if (buffer) delete [] buffer;
		buffer = new char [length + 1];
		memset(buffer, 0, length + 1);
		result = _vsnprintf(buffer, length, fmt, args);
		length *= 2;
	}
	std::string s(buffer);
	delete [] buffer;
	return s;
}

std::string WorldWindow::format(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	std::string s = format_arg_list(fmt, args);
	va_end(args);
	return s;
}

void WorldWindow::Drag(float dt)
{
	int	    dx = x_down - x_last;
	int     dy = y_down - y_last;

	switch ( button )
	{
	case FL_LEFT_MOUSE:
		if (useNewNav == 0) {
			// Left button changes the direction the viewer is looking from.
			theta = theta_down + 360.0f * dx / (float)w();
			while ( theta >= 360.0f )
				theta -= 360.0f;
			while ( theta < 0.0f )
				theta += 360.0f;
			phi = phi_down + 90.0f * dy / (float)h();
			if ( phi > 89.0f )
				phi = 89.0f;
			if ( phi < -5.0f )
				phi = -5.0f;
		}
		else if (useNewNav == 1) {
			// Left button changes the orientation of
			// the viewer. Affects azimuth angle only.
			theta = theta_down - 360.0f * dx / (float)w();
			while ( theta >= 360.0f )
				theta -= 360.0f;
			while ( theta < 0.0f )
				theta += 360.0f;
		}
		break;
	case FL_MIDDLE_MOUSE:
		// Middle button moves the viewer in or out.
		dist = dist_down - ( 0.5f * dist_down * dy / (float)h() );
		if ( dist < 1.0f ) {
			dist = 1.0f;
		}
		break;
	case FL_RIGHT_MOUSE:
		{
			if (useNewNav == 0) {
				// Right mouse button moves the look-at point around, so the world
				// appears to move under the viewer.
				float	x_axis[2];
				float	y_axis[2];

				x_axis[0] = -(float)sin(theta * TwoPi/360.0f);
				x_axis[1] = (float)cos(theta * TwoPi/360.0f);
				y_axis[0] = x_axis[1];
				y_axis[1] = -x_axis[0];

				x_at = x_at_down + 100.0f * ( x_axis[0] * dx / (float)w()
					+ y_axis[0] * dy / (float)h() );
				y_at = y_at_down + 100.0f * ( x_axis[1] * dx / (float)w()
					+ y_axis[1] * dy / (float)h() );
			}
			else if (useNewNav == 1) {
				// Right mouse button changes angle of inclination of
				// viewer's head - e.g. look up or down.
				phi = phi_down + 90.0f * dy / (float)h();
				if ( phi > 89.0f )
					phi = 89.0f;
				if ( phi < -89.0f )
					phi = -89.0f;
			}
			break;
		}
	default:
		break;
	}
}


bool WorldWindow::Update(float dt, int numFrames)
{
	// Update the view. This gets called once per frame before doing the
	// drawing.
	
	// Only do anything if the mouse button is down.
	if ( button != -1 ) {
		Drag(dt);
	}

	// Animate the train.
	if (!m_bPause) {
		m_pRollerCoaster->Update(dt);
		m_pFerrisWheel->Update(dt, numFrames);
		m_pSpinner->Update(dt, numFrames);

		if (useNewNav == 2) {
			GLfloat posn[3];
			GLfloat tangent[3];
			m_pRollerCoaster->listSplineParams.front()->track->Get_Point(m_pRollerCoaster->vec_cars.front()->pos, posn);
			m_x = posn[0];
			m_y = posn[1];
			m_z = posn[2] + m_pRollerCoaster->car_size * 2;

			// ...and what it's orientation is
			m_pRollerCoaster->listSplineParams.front()->track->Evaluate_Derivative(m_pRollerCoaster->vec_cars.front()->pos, tangent);
			Normalize_3(tangent);

			// Rotate it to point along the track, but stay horizontal
			theta = atan2(tangent[1], tangent[0]) * 360.0f/TwoPi;

			// Another rotation to get the tilt right.
			phi = asin(-tangent[2]) * 360.0f/TwoPi;
		}
		else if (useNewNav == 3) {
			GLfloat posn[3];
			GLfloat tangent[3];
			m_pRollerCoaster->listSplineParams.front()->track->Get_Point(m_pRollerCoaster->vec_cars.back()->pos, posn);
			m_x = posn[0];
			m_y = posn[1];
			m_z = posn[2] + m_pRollerCoaster->car_size * 2;

			// ...and what it's orientation is
			m_pRollerCoaster->listSplineParams.front()->track->Evaluate_Derivative(m_pRollerCoaster->vec_cars.back()->pos, tangent);
			Normalize_3(tangent);

			// Rotate it to point along the track, but stay horizontal
			theta = atan2(tangent[1], tangent[0]) * 360.0f/TwoPi;

			// Another rotation to get the tilt right.
			phi = asin(-tangent[2]) * 360.0f/TwoPi;
		}
	}

	return true;
}


void WorldWindow::output(int x, int y, const char *string)
{
  int len, i;

  glRasterPos2f((GLfloat)x, (GLfloat)y);
  len = (int) strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(m_font, string[i]);
  }
}

int WorldWindow::handle(int event)
{
	// Event handling routine. Only looks at mouse events.
	// Stores a bunch of values when the mouse goes down and keeps track
	// of where the mouse is and what mouse button is down, if any.
	switch ( event )
	{
	case FL_KEYBOARD:
		{
			int key = Fl::event_key();
			switch (key) {
			case 'h':
				{
					m_bPrintHelp ^= 1;
					break;
				}
			case 'p':
			case 'P':
				{
					m_bPause ^= 1;
					break;
				}
			case 's':
				{
					if (m_numSubDivides < 5) {
						m_numSubDivides++;
						Mesh* m = m_pSpinner->m_pBase->Subdivide(true);
						delete m_pSpinner->m_pBase->m_pMesh;
						m_pSpinner->m_pBase->m_pMesh = m;
						m_pSpinner->m_pBase->m_pMesh->Initialize();
					}
					break;
				}
			case 'v':
			case 'V':
				{
					useNewNav++;
					if (useNewNav > 3) {
						useNewNav = 0;
					}
					if (useNewNav == 0) {
						phi = 45.0f;
						theta = 0.0f;
						dist = 400.0f;
						x_at = 0.0f;
						y_at = 0.0f;
						z_at = 2.0f;
					}
					else if (useNewNav == 1) {
						phi = 0.0f; // inclination
						theta = 0.0f; // azimuth
						dist = m_parkWidth;
						m_x = 0.0f;
						m_y = 0.0f;
						//ubyte* pixel;
						//pixel = m_heightmap + (int)(m_y+m_parkLength/2) * m_heightmap_width * 3 + (int)(m_x+m_parkWidth/2) * 3;
						m_z = 2.0f + m_pGround->GetHeight(m_x+m_parkWidth/2, m_y+m_parkLength/2);
						//m_z = 2.0f + (255 - (0.299f * (float)pixel[0] + 0.587f * (float)pixel[1] + 0.114f * (float)pixel[2]))/16;
					}
					else if (useNewNav == 2) {
						// On the roller coaster, 2=in last cat, 3=in front car
						phi = 0.0f; // inclination
						theta = 0.0f; // azimuth
						dist = m_parkWidth;
						GLfloat posn[3];
						m_pRollerCoaster->listSplineParams.front()->track->Get_Point(m_pRollerCoaster->vec_cars.front()->pos, posn);
						m_x = posn[0];
						m_y = posn[1];
						m_z = posn[2];
					}
					else if (useNewNav == 3) {
						// On the roller coaster, 2=in last cat, 3=in front car
						phi = 0.0f; // inclination
						theta = 0.0f; // azimuth
						dist = m_parkWidth;
						GLfloat posn[3];
						m_pRollerCoaster->listSplineParams.front()->track->Get_Point(m_pRollerCoaster->vec_cars.back()->pos, posn);
						m_x = posn[0];
						m_y = posn[1];
						m_z = posn[2];
					}
					break;
				}
			case FL_Left:
				{
					if (useNewNav <= 1) {
						m_x -= cos(theta*TwoPi/360.0f);
						m_y += sin(theta*TwoPi/360.0f);
						if (m_x > m_parkWidth/2) {
							m_x = m_parkWidth/2;
						}
						if (m_x < -m_parkWidth/2) {
							m_x = -m_parkWidth/2;
						}
						if (m_y > m_parkLength/2) {
							m_y = m_parkLength/2;
						}
						if (m_y < -m_parkLength/2) {
							m_y = -m_parkLength/2;
						}
						//ubyte* pixel;
						//pixel = m_heightmap + (int)(m_y+m_parkLength/2) * m_heightmap_width * 3 + (int)(m_x+m_parkWidth/2) * 3;
						//m_z = 2.0f + (255 - (0.299f * (float)pixel[0] + 0.587f * (float)pixel[1] + 0.114f * (float)pixel[2]))/16;
						m_z = 2.0f + m_pGround->GetHeight(m_x+m_parkWidth/2, m_y+m_parkLength/2);
				}
				return 1;
				}
			case FL_Right:
				{
				if (useNewNav <= 1) {
					m_x += cos(theta*TwoPi/360.0f);
					m_y -= sin(theta*TwoPi/360.0f);
					if (m_x > m_parkWidth/2) {
						m_x = m_parkWidth/2;
					}
					if (m_x < -m_parkWidth/2) {
						m_x = -m_parkWidth/2;
					}
					if (m_y > m_parkLength/2) {
						m_y = m_parkLength/2;
					}
					if (m_y < -m_parkLength/2) {
						m_y = -m_parkLength/2;
					}
					//ubyte* pixel;
					//pixel = m_heightmap + (int)(m_y+m_parkLength/2) * m_heightmap_width * 3 + (int)(m_x+m_parkWidth/2) * 3;
					//m_z = 2.0f + (255 - (0.299f * (float)pixel[0] + 0.587f * (float)pixel[1] + 0.114f * (float)pixel[2]))/16;
					m_z = 2.0f + m_pGround->GetHeight(m_x+m_parkWidth/2, m_y+m_parkLength/2);
				}
				return 1;
				}
			case FL_Up:
				{
				if (useNewNav <= 1) {
					m_x += sin(theta*TwoPi/360.0f);
					m_y += cos(theta*TwoPi/360.0f);
					if (m_x > m_parkWidth/2) {
						m_x = m_parkWidth/2;
					}
					if (m_x < -m_parkWidth/2) {
						m_x = -m_parkWidth/2;
					}
					if (m_y > m_parkLength/2) {
						m_y = m_parkLength/2;
					}
					if (m_y < -m_parkLength/2) {
						m_y = -m_parkLength/2;
					}
					//ubyte* pixel;
					//pixel = m_heightmap + (int)(m_y+m_parkLength/2) * m_heightmap_width * 3 + (int)(m_x+m_parkWidth/2) * 3;
					//m_z = 2.0f + (255 - (0.299f * (float)pixel[0] + 0.587f * (float)pixel[1] + 0.114f * (float)pixel[2]))/16;
					m_z = 2.0f + m_pGround->GetHeight(m_x+m_parkWidth/2, m_y+m_parkLength/2);
				}
				return 1;
				}
			case FL_Down:
				{
					if (useNewNav <= 1) {
						m_x -= sin(theta*TwoPi/360.0f);
						m_y -= cos(theta*TwoPi/360.0f);
						if (m_x > m_parkWidth/2) {
							m_x = m_parkWidth/2;
						}
						if (m_x < -m_parkWidth/2) {
							m_x = -m_parkWidth/2;
						}
						if (m_y > m_parkLength/2) {
							m_y = m_parkLength/2;
						}
						if (m_y < -m_parkLength/2) {
							m_y = -m_parkLength/2;
						}
						//ubyte* pixel;
						//pixel = m_heightmap + (int)(m_y+m_parkLength/2) * m_heightmap_width * 3 + (int)(m_x+m_parkWidth/2) * 3;
						m_z = 2.0f + m_pGround->GetHeight(m_x+m_parkWidth/2, m_y+m_parkLength/2);
						//(255 - (0.299f * (float)pixel[0] + 0.587f * (float)pixel[1] + 0.114f * (float)pixel[2]))/16;
					}
				return 1;
				}
			}
		}
		break;
	case FL_PUSH:
		button = Fl::event_button();
		x_last = x_down = Fl::event_x();
		y_last = y_down = Fl::event_y();
		phi_down = phi;
		theta_down = theta;
		dist_down = dist;
		x_at_down = x_at;
		y_at_down = y_at;
		return 1;
	case FL_DRAG:
		x_last = Fl::event_x();
		y_last = Fl::event_y();
		return 1;
	case FL_RELEASE:
		button = -1;
		return 1;
	}

	// Pass any other event types on the superclass.
	return Fl_Gl_Window::handle(event);
}


