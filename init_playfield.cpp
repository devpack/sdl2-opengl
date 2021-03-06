#include "init_playfield.h"

/*---------------------------------------------------------------------------*/

InitPlayfield::InitPlayfield(int screen_width, int screen_height, bool fullscreen, bool vsync)
{
	this->screen_width = screen_width;
	this->screen_height = screen_height;
	
	// DSL init
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Failed to init SDL\n";
	}

	int window_flag = SDL_WINDOW_OPENGL;

	if(fullscreen)
		window_flag |= SDL_WINDOW_FULLSCREEN_DESKTOP;

	// Create our window centered
	mainWindow = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->screen_width, this->screen_height, window_flag);

	// check
	if (!mainWindow)
	{
		std::cout << "Unable to create window\n";

	    std::string error = SDL_GetError();

	    if (error != "")
	    {
		    std::cout << "SLD Error : " << error << std::endl;

		    if (__LINE__ != -1)
			    std::cout << "\nLine : " << __LINE__ << std::endl;

		    SDL_ClearError();
	    }
	}

	// Create our opengl context and attach it to our window
	mainContext = SDL_GL_CreateContext(mainWindow);
	
	// SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// 3.2 is part of the modern versions of OpenGL, but most video cards whould be able to run it
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	// Turn on double buffering with a 24bit Z buffer.
	// You may need to change this to 16 or 32 for your system
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	// mouse within
	SDL_SetRelativeMouseMode(SDL_TRUE);

	// This makes our buffer swap syncronized with the monitor's vertical refresh 
	// 1 => vsync (+-60 fps)
	// 0 => don't wait the vsync (more fps)
	if(vsync) {
		SDL_GL_SetSwapInterval(1);
	}
	else {
		SDL_GL_SetSwapInterval(0);
	}

	// GLEW
    glewExperimental = GL_TRUE;
    auto init_res = glewInit();
    if(init_res != GLEW_OK)
    {
        std::cout << glewGetErrorString(glewInit()) << std::endl;
    }

}

/*---------------------------------------------------------------------------*/

InitPlayfield::~InitPlayfield()
{
	// Delete our OpengL context
	SDL_GL_DeleteContext(mainContext);

	// Destroy our window
	SDL_DestroyWindow(mainWindow);

	// Shutdown SDL 2
	SDL_Quit();
}



