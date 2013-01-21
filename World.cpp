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
 * World.cpp: Main program file for Project 3, CS 559
 *
 * (c) 2001-2002: Stephen Chenney
 */


#include <Fl/Fl.h>
#include "WorldWindow.h"
#include <stdio.h>
#include <iostream>

// The time per frame, in seconds (enforced only by timeouts.)
static const float  FRAME_TIME = 0.025f;

// The dimensions of the park
static const int PARK_WIDTH = 256;
static const int PARK_LENGTH = 256;

static const int WINDOW_WIDTH = 800;
static const int WINDOW_HEIGHT = 600;

static WorldWindow *world_window; // The window with world view in it


// This callback is called every 40th of a second if the system is fast
// enough. You should change the variable FRAME_TIME defined above if you
// want to change the frame rate.
static void
Timeout_Callback(void *data)
{
    static int numFrames = 0;
	
	// Update the motion in the world. This both moves the view and
    // animates the train.
    numFrames++;
	world_window->Update(FRAME_TIME, numFrames);
    world_window->redraw();

    // Do the timeout again for the next frame.
    Fl::repeat_timeout(FRAME_TIME, Timeout_Callback);
}


int
main(int argc, char *argv[])
{
    Fl::visual(FL_RGB);

    world_window = new WorldWindow(PARK_WIDTH, PARK_LENGTH, WINDOW_WIDTH, WINDOW_HEIGHT, "World");
	world_window->init();

    world_window->show(argc, argv);

    Fl::add_timeout(0.0, Timeout_Callback, NULL);

	std::cout << "Starting FL::run().\n" << std::flush;
	
	return Fl::run();
}


