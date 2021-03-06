#include "init_playfield.h"
#include "camera.h"
#include "render.h"
#include "timer.h"

#include <sstream>

/*---------------------------- EVENTS <=> Camera ----------------------------*/

void process_mouse(Camera *camera, const SDL_MouseMotionEvent & event) {
	camera->ProcessMouse((float)event.xrel, (float)event.yrel);
}

/*--------------------------------- LOOP ------------------------------------*/

void game_loop(InitPlayfield *playfield, Camera *camera, Render *render) {

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//SDL_GL_SwapWindow(playfield->mainWindow);

	// FPS timer
    Timer fps_timer;
	fps_timer.start();

    int frame = 0;

    // title timer
    Timer title_timer;
    title_timer.start();

	// key camera motion
	bool forward = false;
	bool backward = false;
	bool left = false;
	bool right = false;
	bool up = false;
	bool down = false;

	// main loop
	bool loop = true;

	while (loop)
	{
		// SDL2 events
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{

			if(event.type == SDL_QUIT) {
				loop = false;
				break;
			}

			// mouse
			if(event.type == SDL_MOUSEMOTION) {
				process_mouse(camera, event.motion);
			}

			// key up
			if(event.type == SDL_KEYDOWN) {

				if(event.key.keysym.sym == SDLK_ESCAPE) {
					loop = false;
					break;
				}

				if(event.key.keysym.sym == SDLK_UP)
					forward = true;
				if (event.key.keysym.sym == SDLK_DOWN)
					backward = true;

				if(event.key.keysym.sym == SDLK_LEFT)
					left = true;
				if(event.key.keysym.sym == SDLK_RIGHT)
					right = true;

				if(event.key.keysym.sym == SDLK_q)
					up = true;
				if(event.key.keysym.sym == SDLK_w)
					down = true;
			}

			// key down
			if(event.type == SDL_KEYUP) {

				if(event.key.keysym.sym == SDLK_UP)
					forward = false;
				if (event.key.keysym.sym == SDLK_DOWN)
					backward = false;

				if(event.key.keysym.sym == SDLK_LEFT)
					left = false;
				if(event.key.keysym.sym == SDLK_RIGHT)
					right = false;

				if(event.key.keysym.sym == SDLK_q)
					up = false;
				if(event.key.keysym.sym == SDLK_w)
					down = false;
			}

		} // end while poll event


		// clear
        glClear(GL_COLOR_BUFFER_BIT);

		// camera moves
		camera->ProcessKeyboard(forward, backward, left, right, up, down);
		camera->CameraTransformations();

		// scene
		render->Scene();

		// show back buffer
		SDL_GL_SwapWindow(playfield->mainWindow);

		// FPS
        frame++;

        // update once per sec
        if( title_timer.get_ticks() > 1000 ) 
		{
            std::stringstream s;

            s << "FPS: " << frame / ( fps_timer.get_ticks() / 1000.f );

			SDL_SetWindowTitle(playfield->mainWindow, s.str().c_str());

            title_timer.start();
        }

	} // end while loop
} 

/*--------------------------------- MAIN ------------------------------------*/

// screen globals
const int screen_width = 1280;
const int screen_height = 800;
bool fullscreen = false;
bool vsync = true;

// camera globals
GLfloat xcamera = 0.0;
GLfloat ycamera_height = 0.0;
GLfloat zcamera_distance = 5.0;
GLfloat znear = 1.0;   // Frustum culling znear
GLfloat zfar = 1000.0; // Frustum culling zfar
GLfloat angle_view = 45.0;
GLfloat mouse_sensitivity = 0.1;
GLfloat key_forward_sensitivity = 0.2;
GLfloat key_lateral_sensitivity = 1.0;
GLfloat key_height_sensitivity = 0.1;

int main(int argc, char* argv[]) 
{     
	// SDL screen: InitPlayfield(fullscreen, vsync)
    InitPlayfield *playfield=new InitPlayfield(screen_width, screen_height, fullscreen, vsync);

	// screen size
	int actual_screen_width, actual_screen_height;
	SDL_GetWindowSize(playfield->mainWindow, &actual_screen_width, &actual_screen_height);
	std::cout << "Screen size: " << actual_screen_width << "x" << actual_screen_height << std::endl;

    // Camera(actual_screen_width, actual_screen_height, xcamera, ycamera_height, zcamera_distance, znear, zfar, angle_view, mouse_sensitivity, key_forward_sensitivity, key_lateral_sensitivity, key_height_sensitivity);
 	Camera *camera = new Camera(actual_screen_width, actual_screen_height, xcamera, ycamera_height, zcamera_distance, znear, zfar, angle_view, 
	 							mouse_sensitivity, key_forward_sensitivity, key_lateral_sensitivity, key_height_sensitivity);

	// render->Scene() used in the main loop
 	Render *render = new Render();

	// main loop
	game_loop(playfield, camera, render);

    delete playfield;
    delete camera;

    return 0;
}
