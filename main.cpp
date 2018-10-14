/*Graphics2d - J.Benoit - Oct 13, 2018
  A framework for creating some simple 2D graphics.
  This wraps SDL functions to make them even simpler.
 
  For Mac OS X, downloaded SDL2 source code tar.gz from
  https://www.libsdl.org/. The '.dmg' version only works in XCode
  (not NetBeans). Installed tar.gz using usual 'configure/make/make install'
  routine. 
  After creating a NetBeans project, right-click the project name in the
  project browser pane (on left), go to 'Set Configuration'->'Customize'.
  Click 'C++ compiler' and under 'Additional Options' add '-framework cocoa'.
  Then under 'Linker', 'Libraries', add 'SDL2' & 'SDL2Main'. Make sure to add
  them as 'Libraries', not 'Library Files'.
 
  Using example code from http://lazyfoo.net/tutorials/SDL.
*/

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_main.h"

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();       //Starts up SDL and creates window
bool loadMedia();  //Loads media
void close();      //Frees media and shuts down SDL

SDL_Window* gWindow = NULL; //The window we'll be rendering to
SDL_Surface* gScreenSurface = NULL;//The surface contained by the window
SDL_Surface* gHelloWorld = NULL; //The image we will load and show on the screen

//============================================================================
int main( int argc, char* args[] )
{
    //Start up SDL and create window
    if( !init() )
        cout << "Failed to initialize!" << endl;
    else {
        //Load media
        if( !loadMedia() )
            cout << "Failed to load media!" << endl;
        else {
            //Apply the image
            SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );
			
            //Update the surface
            SDL_UpdateWindowSurface( gWindow );

            //Wait two seconds
            SDL_Delay( 10000 );
        }
    }

    close();  //Free resources and close SDL

    return 0;
}

//============================================================================
bool init()
{
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError()
             << endl;
        success = false;
    }
    else {
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", 
                    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                    SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL ) {
            cout << "Window could not be created! SDL_Error: "
                 << SDL_GetError() << endl;
            success = false;
        }
        else {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }

    return success;
}

//============================================================================
bool loadMedia()
{
    bool success = true;

    //Load splash image
    gHelloWorld = SDL_LoadBMP( "hello_world.bmp" );
    if( gHelloWorld == NULL ) {
        cout << "Unable to load image " << "hello_world.bmp"
             << "! SDL Error: " << SDL_GetError() << endl;
	success = false;
    }

    return success;
}

//============================================================================
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