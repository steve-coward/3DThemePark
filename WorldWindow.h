/*
 * CS559 Maze Project
 *
 * Class header file for the WorldWindow class. The WorldWindow is
 * the window in which the viewer's view of the world is displayed.
 *
 * (c) Stephen Chenney, University of Wisconsin at Madison, 2001-2002
 *
 */

#ifndef _WORLDWINDOW_H_
#define _WORLDWINDOW_H_

#include <string>
#include <list>
#include <Fl/Fl.h>
#include <Fl/Fl_Gl_Window.h>
#include "Ground.h"
#include "Track.h"
#include "Tree.h"
#include "Bridge.h"
#include "Spinner.h"
#include "FerrisWheel.h"
#include "Fence.h"
#include "SurfRev.h"
#include "libtarga.h"


// Subclass the Fl_Gl_Window because we want to draw OpenGL in here.
class WorldWindow : public Fl_Gl_Window {
    public:
	// Constructor takes window position and dimensions, the title.
	WorldWindow(int x, int y, int w, int h, char *label);
	// Call after constructor
	void init(void);

	~WorldWindow();

	bool m_bPause;
	bool m_bUseHeightMap;

	GLfloat m_parkWidth;
	GLfloat m_parkLength;
	GLint m_windowWidth;
	GLint m_windowHeight;

	// draw() method invoked whenever the view changes or the window
	// otherwise needs to be redrawn.
	void	draw(void);

	bool m_bPrintHelp;
	void *m_font;
	void output(int x, int y, const char *string);
	std::string format_arg_list(const char *fmt, va_list args);
	std::string format(const char *fmt, ...);
	void setOrthographicProjection();
	void resetPerspectiveProjection();

	// Event handling method. Uses only mouse events.
	int	handle(int);

	// Update the world according to any events that have happened since
	// the last time this method was called.
	bool	Update(float dt, int numFrames);

    private:
	Ground*	m_pGround; // The ground object.
	Track* m_pRollerCoaster; // The rollercoaster.
	FerrisWheel* m_pFerrisWheel; // The Feris Wheel.
	//SurfRev* m_pSurfRevf;
	//SurfRev* m_pSurfRevl;
	Fence* m_pFence;
	Bridge* m_pBridge1;
	Bridge* m_pBridge2;
	Spinner* m_pSpinner;
	//Mesh* m_pMesh;
	std::list<Tree*> m_listTrees;
	std::list<Mesh*> m_listFence;

	ubyte* m_heightmap;
    int	m_heightmap_height;
	int	m_heightmap_width;
	int m_numSubDivides;

	static const double FOV_X; // The horizontal field of view.

	int	useNewNav;
	float	phi;	// Viewer's inclination angle.
	float	theta;	// Viewer's azimuthal angle.
	float	dist;	// Viewer's distance from the look-at point.
	float	x_at;	// The x-coord to look at.
	float	y_at;	// The y-coord to look at. z_at is assumed 2.0.
	float	z_at;	// The z-coord to look at. z_at is assumed 2.0.
	float m_x;
	float m_y;
	float m_z;

	int     button;	// The mouse button that is down, -1 if none.
	int	x_last;	// The location of the most recent mouse event
	int	y_last;
	int	x_down; // The location of the mouse when the button was pushed
	int	y_down;
	float   phi_down;   // The view inclination angle when the mouse
			    // button was pushed
	float   theta_down; // The view azimuthal angle when the mouse
			    // button was pushed
	float	dist_down;  // The distance when the mouse button is pushed.
	float	x_at_down;  // The x-coord to look at when the mouse went down.
	float	y_at_down;  // The y-coord to look at when the mouse went down.

	void	Drag(float);	// The function to call for mouse drag events
};


#endif
