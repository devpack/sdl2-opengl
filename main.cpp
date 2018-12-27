#include "init_playfield.h"
#include "camera.h"
#include "render.h"

/*---------------------------- EVENTS <=> Camera ----------------------------*/

void process_mouse(Camera *camera, const SDL_MouseMotionEvent & event) {
	camera->ProcessMouse((float)event.xrel, (float)event.yrel);
}

/*--------------------------------- LOOP ------------------------------------*/

void game_loop(InitPlayfield *playfield, Camera *camera, Render *render) {

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//SDL_GL_SwapWindow(playfield->mainWindow);

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

	} // end while loop
} 

/*--------------------------------- MAIN ------------------------------------*/

int main(int argc, char* argv[]) 
{     
	// SDL screen
    InitPlayfield *playfield=new InitPlayfield();

    // Camera(screen_width, screen_height, xcamera, ycamera_height, zcamera_distance, znear, zfar, angle_view, mouse_sensitivity, key_forward_sensitivity, key_lateral_sensitivity, key_height_sensitivity);
 	Camera *camera = new Camera(playfield->screen_width, playfield->screen_height, 0.0, 0.0, 5.0, 1.0, 1000.0, 45.0, 0.1, 0.2, 1.0, 0.1);

	// render->Scene() used in the main loop
 	Render *render = new Render();

	// main loop
	game_loop(playfield, camera, render);

    delete playfield;
    delete camera;

    return 0;
}
