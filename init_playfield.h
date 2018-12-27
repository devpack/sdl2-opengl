#ifndef __INITPLAYFIELD_H_
#define __INITPLAYFIELD_H_

#include <string>
#include <iostream>

//#define GL3_PROTOTYPES 1
#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "math.h"

/*---------------------------------------------------------------------------*/

class InitPlayfield
{
public:
       int screen_width;
       int screen_height;

        // Our SDL_Window
        SDL_Window *mainWindow;

        // Our opengl context handle
        SDL_GLContext mainContext;

public:
       InitPlayfield(int screen_width, int screen_height, bool fullscreen, bool vsync);
       virtual ~InitPlayfield();
};

#endif
