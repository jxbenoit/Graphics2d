/*Graphics2d - J.Benoit - Oct 13, 2018
  A framework for creating some simple 2D graphics.
  This wraps SDL functions to make them even simpler.
*/

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_main.h"

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


bool init();//Starts up SDL and creates window
bool loadMedia();//Loads media
void close();//Frees media and shuts down SDL

SDL_Window* gWindow = NULL; //The window we'll be rendering to
SDL_Surface* gScreenSurface = NULL;//The surface contained by the window
SDL_Surface* gHelloWorld = NULL; //The image we will load and show on the screen

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
            printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
            success = false;
	}
	else {
            //Create window
            gWindow = SDL_CreateWindow( "SDL Tutorial", 
                    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                    SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
            if( gWindow == NULL ) {
                printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		success = false;
            }
            else {
                //Get window surface
		gScreenSurface = SDL_GetWindowSurface( gWindow );
            }
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image
	gHelloWorld = SDL_LoadBMP( "hello_world.bmp" );
	if( gHelloWorld == NULL ) {
		printf( "Unable to load image %s! SDL Error: %s\n", "hello_world.bmp", SDL_GetError() );
		success = false;
	}

	return success;
}

void close()
{
	//Deallocate surface
	SDL_FreeSurface( gHelloWorld );
	gHelloWorld = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
		printf( "Failed to initialize!\n" );
	else {
		//Load media
		if( !loadMedia() )
			printf( "Failed to load media!\n" );
		else {
			//Apply the image
			SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );
			
			//Update the surface
			SDL_UpdateWindowSurface( gWindow );

			//Wait two seconds
			SDL_Delay( 10000 );
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}

/*
int main(int argc, char** argv) {
   //The images
    SDL_Surface* hello = NULL;
//    SDL_Surface* screen = NULL;

    //Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );

    //Set up screen
SDL_Window* window = SDL_CreateWindow("NAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
//    screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );

    //Load image
    hello = SDL_LoadBMP( "hello.bmp" );
//    cout << "hello=" << hello << endl;

    //Apply image to screen
//    SDL_BlitSurface( hello, NULL, screen, NULL );
    //Update Screen
//    SDL_Flip( screen ); 
        //Pause
    SDL_Delay( 10000 );

     //Free the loaded image
    SDL_FreeSurface( hello );
SDL_DestroyWindow(window);

    //Quit SDL
    SDL_Quit(); 
    
    return 0;
}

*/