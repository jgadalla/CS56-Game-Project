 #include <SDL2/SDL.h>
 #include <SDL2_image/SDL_image.h>
 #include <stdio.h>

 #include <cstdio>
 #include <cstdlib>
 #include <ctime>
 #include <iostream>

//  #include "Bullet.hpp"
 #include "Enemy.hpp"
 #include "LTexture.hpp"
 #include "Queue.hpp"
 #include "Unit.hpp"


 //Pre defined screen width and height
 const int SCREEN_WIDTH = 792;
 const int SCREEN_HEIGHT = 468;

 //road intersection locations
 const int XMID = SCREEN_WIDTH/2;
 const int YMID = SCREEN_HEIGHT/2;
 const int XMAX = SCREEN_WIDTH;
 const int YMAX = SCREEN_HEIGHT;

 //direction locations clockwise 
 int north = 0;
 int east = 1;
 int south = 2;
 int west = 3;

 bool init();

 bool loadMedia();

 void close();

 SDL_Window* gWindow = NULL;

 SDL_Renderer* gRenderer = NULL;

 LTexture gSpriteSheetTexture;

 //screen textures 
 LTexture startTexture;
 LTexture gameTexture;
 LTexture carTexture;

 //start game boolean   ------------------------------
 bool startGame = false;

 bool init();
 bool loadMedia();
 void close();

 int check_click_in_rect(int x, int y, SDL_Rect *rect)
{
    /* Check X coordinate is within rectangle range */
    if (x >= rect->x && x < (rect->x + rect->w))
    {
        /* Check Y coordinate is within rectangle range */
        if (y >= rect->y && y < (rect->y + rect->h))
        {
            /* X and Y is inside the rectangle */
            return 1;
        }
    }

    /* X or Y is outside the rectangle */
    return 0;
}

 int main( int argc, char* args[] )
 {
   //Start up SDL and create window
   if( !init() )
     {
       printf( "Failed to initialize!\n" );
     }
   else
     {
       //Load media
       if( !loadMedia() )
     {
       printf( "Failed to load media!\n" );
     }
       else
     {

       //Main loop flag
			 bool start_screen = true;
       bool quit = false;      

       SDL_Event e;                            //Event handler

       long int frame = 0;                     //Current animation frame
       //int bulletDelay = 0;

       /* initialize random seed: */
       srand (time(NULL));

       /* generate secret number between 1 and 10: */
       int random = 0;

       Queue objectList;

       //Unit* plane = new Unit(&carTexture, 0, (float)SCREEN_HEIGHT/2);
       Unit* enemy = NULL;
       //Unit* bullet = NULL;


       while( !quit )                          //While application is running
         {
           if(frame%240 == 0)
                 {
           random = rand() % SCREEN_WIDTH;
           enemy = new Enemy(&carTexture, (float)SCREEN_WIDTH/2 - 30, -50);
           objectList.Enqueue(enemy);
                 }

          // printf("Start of game loop\n");

          // this code does not show a button on the screen
          // change needed here
          SDL_Rect* start_button = new SDL_Rect();
          start_button->x = 286;
          start_button->y = 132;
          start_button->w = 208;
          start_button->h = 57;
          SDL_RenderDrawRect(gRenderer, start_button);

          // printf("Drawn Rectangle\n");


           while( SDL_PollEvent( &e ) != 0 )   //Handle events on queue
         {


           //User requests quit
           if( e.type == SDL_QUIT )
             {
               quit = true;
             }


         }

         if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP){
					int x, y;
					SDL_GetMouseState(&x, &y);
					if(e.type == SDL_MOUSEBUTTONUP && check_click_in_rect(x,y,start_button)){
						start_screen = false;
            frame = 0;
					}
				}

           const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

        //    if(currentKeyStates[ SDL_SCANCODE_RIGHT ])
        //  {
        //    plane->Move(RIGHT);
        //  }

        //    if(currentKeyStates[ SDL_SCANCODE_LEFT ])
        //  {
        //    plane->Move(LEFT);
        //  }

        //    if(currentKeyStates[ SDL_SCANCODE_UP ])
        //  {
        //    plane->Move(UP);
        //  }

        //    if(currentKeyStates[ SDL_SCANCODE_DOWN ])
        //  {
        //    plane->Move(DOWN);
        //  }

        //    if(currentKeyStates[ SDL_SCANCODE_SPACE ])
        //  {
        //   //  if(bulletDelay > 60)
        //   //    {
        //   //      bullet = new Bullet(&gSpriteSheetTexture,plane->GetX(), plane->GetY() - plane->GetHeight()/2);
        //   //      objectList.Enqueue(bullet);
        //   //      bulletDelay = 0;
        //   //    }
        //  }

           SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );    //Clear screen
           SDL_RenderClear( gRenderer );

          if(start_screen){
            startTexture.Render(0, 0, gRenderer);
          }
          else{
            gameTexture.Render(0, 0, gRenderer);
            // plane->Render(gRenderer);
            // plane->Move();
            // objectList.Render(frame, gRenderer, false);
            objectList.Render(gRenderer);
            objectList.Move();
          }

          //  objectList.Clean();
           SDL_RenderPresent( gRenderer );     //Update screen

           ++frame;                            //Go to next frame
           //++bulletDelay;

         }
       //delete plane;
     }
     }

   //Free resources and close SDL
   close();

   return 0;
 }

 bool init()
 {
   //Initialization flag
   bool success = true;

   //Initialize SDL
   if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
     {
       printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
       success = false;
     }
   else
     {
       //Set texture filtering to linear
       if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
     {
       printf( "Warning: Linear texture filtering not enabled!" );
     }

       //Create window
       gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
       if( gWindow == NULL )
     {
       printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
       success = false;
     }
       else
     {
       //Create renderer for window
       gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
       if( gRenderer == NULL )
             {
           printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
           success = false;
             }
       else
         {
           //Initialize renderer color
           SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

           //Initialize PNG loading
           int imgFlags = IMG_INIT_PNG;
           if( !( IMG_Init( imgFlags ) & imgFlags ) )
         {
           printf( "SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError() );
           success = false;
         }
         }
     }
     }

   return success;
 }

 bool loadMedia()
 {
   //Loading success flag
   bool success = true;

   //Load sprite sheet texture
   if( !gSpriteSheetTexture.LoadFromFile( "Images/1948.png", gRenderer  ) )
     {
       printf( "Failed to load sprite sheet texture!\n" );
       success = false;
     }


  if( !startTexture.LoadFromFile( "Images/Start-Screen.png", gRenderer ) )
	{
		printf( "Failed to load Foo' texture image!\n" );
		success = false;
	}

  if( !carTexture.LoadFromFile( "Images/red.png", gRenderer ) )
	{
		printf( "Failed to load Foo' texture image!\n" );
		success = false;
	}
	
	if( !gameTexture.LoadFromFile( "Images/roadtile.png", gRenderer ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}

   return success;
 }

 void close()
 {
   //Free loaded images
   gSpriteSheetTexture.Free();
   gameTexture.Free();
   startTexture.Free();
   carTexture.Free();

   //Destroy window
   SDL_DestroyRenderer( gRenderer );
   SDL_DestroyWindow( gWindow );
   gWindow = NULL;
   gRenderer = NULL;

   //Quit SDL subsystems
   IMG_Quit();
   SDL_Quit();
 }


// /*This source code copyrighted by Lazy Foo' Productions (2004-2019)
// and may not be redistributed without written permission.*/

// //Using SDL, SDL_image, standard IO, and strings
// #include <SDL2/SDL.h>
// #include <SDL2_image/SDL_image.h>
// #include <stdio.h>
// #include <string>
// #include <iostream>

// //Screen dimension constants
// const int SCREEN_WIDTH = 792;
// const int SCREEN_HEIGHT = 469;

// //Texture wrapper class
// class LTexture
// {
// 	public:
// 		//Initializes variables
// 		LTexture();

// 		//Deallocates memory
// 		~LTexture();

// 		//Loads image at specified path
// 		bool loadFromFile( std::string path );

// 		//Deallocates texture
// 		void free();

// 		//Renders texture at given point
// 		void render( int x, int y );

// 		//Gets image dimensions
// 		int getWidth();
// 		int getHeight();

// 	private:
// 		//The actual hardware texture
// 		SDL_Texture* mTexture;

// 		//Image dimensions
// 		int mWidth;
// 		int mHeight;
// };


// //Starts up SDL and creates window
// bool init();

// //Loads media
// bool loadMedia();

// //Frees media and shuts down SDL
// void close();

// //Loads individual image
// SDL_Surface* loadSurface( std::string path );

// //The window we'll be rendering to
// SDL_Window* gWindow = NULL;
	
// //The surface contained by the window
// //SDL_Surface* gScreenSurface = NULL;

// //Current displayed PNG image
// // SDL_Surface* gStartSurface = NULL;
// // SDL_Surface* gGameSurface = NULL;

// //Current renderer for shapes
// SDL_Renderer* gRenderer = NULL;

// //Scene textures
// LTexture startTexture;
// LTexture gameTexture;

// LTexture::LTexture()
// {
// 	//Initialize
// 	mTexture = NULL;
// 	mWidth = 0;
// 	mHeight = 0;
// }

// LTexture::~LTexture()
// {
// 	//Deallocate
// 	free();
// }

// bool LTexture::loadFromFile( std::string path )
// {
// 	//Get rid of preexisting texture
// 	free();

// 	//The final texture
// 	SDL_Texture* newTexture = NULL;

// 	//Load image at specified path
// 	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
// 	if( loadedSurface == NULL )
// 	{
// 		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
// 	}
// 	else
// 	{
// 		// //Color key image
// 		// SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

// 		//Create texture from surface pixels
//         newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
// 		if( newTexture == NULL )
// 		{
// 			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
// 		}
// 		else
// 		{
// 			//Get image dimensions
// 			mWidth = loadedSurface->w;
// 			mHeight = loadedSurface->h;
// 		}

// 		//Get rid of old loaded surface
// 		SDL_FreeSurface( loadedSurface );
// 	}

// 	//Return success
// 	mTexture = newTexture;
// 	return mTexture != NULL;
// }

// void LTexture::free()
// {
// 	//Free texture if it exists
// 	if( mTexture != NULL )
// 	{
// 		SDL_DestroyTexture( mTexture );
// 		mTexture = NULL;
// 		mWidth = 0;
// 		mHeight = 0;
// 	}
// }

// void LTexture::render( int x, int y )
// {
// 	//Set rendering space and render to screen
// 	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
// 	SDL_RenderCopy( gRenderer, mTexture, NULL, &renderQuad );
// }

// int LTexture::getWidth()
// {
// 	return mWidth;
// }

// int LTexture::getHeight()
// {
// 	return mHeight;
// }


// int check_click_in_rect(int x, int y, SDL_Rect *rect)
// {
//     /* Check X coordinate is within rectangle range */
//     if (x >= rect->x && x < (rect->x + rect->w))
//     {
//         /* Check Y coordinate is within rectangle range */
//         if (y >= rect->y && y < (rect->y + rect->h))
//         {
//             /* X and Y is inside the rectangle */
//             return 1;
//         }
//     }

//     /* X or Y is outside the rectangle */
//     return 0;
// }

// bool init()
// {
// 	//Initialization flag
// 	bool success = true;

// 	//Initialize SDL
// 	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
// 	{
// 		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
// 		success = false;
// 	}
// 	else
// 	{

// 		  //Set texture filtering to linear
//        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
//      {
//        printf( "Warning: Linear texture filtering not enabled!" );
//      }

// 		//Create window
// 		gWindow = SDL_CreateWindow( "Sixth Street Scramble", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
// 		if( gWindow == NULL )
// 		{
// 			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
// 			success = false;
// 		}
// 		else
// 		{
// 			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
// 			if (gRenderer == NULL)
// 			{
// 				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
// 				success = false;
// 			}
// 			else
// 			{
// 				//Initialize renderer color
// 				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	
// 			//Initialize PNG loading
// 			int imgFlags = IMG_INIT_PNG;
// 			if( !( IMG_Init( imgFlags ) & imgFlags ) )
// 			{
// 				printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
// 				success = false;
// 			}
// 			}
// 			// else
// 			// {
// 			// 	//Get window surface
// 			// 	gScreenSurface = SDL_GetWindowSurface( gWindow );
// 			// }

// 			// //Get window surface
//             // gScreenSurface = SDL_GetWindowSurface( gWindow );
// 		}
// 	}

// 	return success;
// }

// bool loadMedia()
// {
// 	//Loading success flag
// 	bool success = true;

// 	//Load PNG surface into textures 

//     if( !startTexture.loadFromFile( "Start-Screen.png" ) )
// 	{
// 		printf( "Failed to load Foo' texture image!\n" );
// 		success = false;
// 	}
	
// 	if( !gameTexture.loadFromFile( "Game-Screen.png" ) )
// 	{
// 		printf( "Failed to load background texture image!\n" );
// 		success = false;
// 	}


// 	// gStartSurface = loadSurface( "Start-Screen.png" );
// 	// if( gStartSurface== NULL )
// 	// {
// 	// 	printf( "Failed to load PNG image!\n" );
// 	// 	success = false;
// 	// }
// 	// gGameSurface = loadSurface( "Game-Screen.png" );
// 	// if( gGameSurface== NULL )
// 	// {
// 	// 	printf( "Failed to load PNG image!\n" );
// 	// 	success = false;
// 	// }

// 	// SDL_Texture* startTexture = 
// 	// 	SDL_CreateTextureFromSurface(gRenderer ,gStartSurface);
// 	// SDL_Texture* gameTexture = 
// 	// 	SDL_CreateTextureFromSurface(gRenderer ,gGameSurface);	


// 	return success;
// }

// void close()
// {
// 	//Free loaded image
//     gameTexture.free();
//     startTexture.free();

// 	// SDL_FreeSurface( gGameSurface );
// 	// gGameSurface = NULL;
// 	// SDL_FreeSurface( gStartSurface );
// 	// gStartSurface = NULL;

// 	// SDL_DestroyRenderer( gRenderer );
// 	// gRenderer = NULL;

// 	//Destroy window
//     SDL_DestroyRenderer(gRenderer);
// 	SDL_DestroyWindow( gWindow );
// 	gWindow = NULL;
//     gRenderer = NULL;

// 	//Quit SDL subsystems
// 	IMG_Quit();
// 	SDL_Quit();
// }
// // ------- Done withing the texture class --------
// // SDL_Surface* loadSurface( std::string path )
// // {
// // 	//The final optimized image
// // 	SDL_Surface* optimizedSurface = NULL;

// // 	//Load image at specified path
// // 	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
// // 	if( loadedSurface == NULL )
// // 	{
// // 		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
// // 	}
// // 	else
// // 	{
// // 		//Convert surface to screen format
// // 		optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
// // 		if( optimizedSurface == NULL )
// // 		{
// // 			printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
// // 		}

// // 		//Get rid of old loaded surface
// // 		SDL_FreeSurface( loadedSurface );
// // 	}

// // 	return optimizedSurface;
// // }
// //--------------

// int main( int argc, char* args[] )
// {
// 	//Start up SDL and create window
// 	if( !init() )
// 	{
// 		printf( "Failed to initialize!\n" );
// 	}
// 	else
// 	{
// 		//Load media
// 		if( !loadMedia() )
// 		{
// 			printf( "Failed to load media!\n" );
// 		}
// 		else
// 		{	
// 			//Main loop flag
// 			bool quit = false;
// 			bool start_screen = true;


// 			//Event handler
// 			SDL_Event e;

// 			//While application is running
// 			while( !quit )
// 			{
// 				printf("Start of game loop\n");

// 				SDL_Rect* start_button = new SDL_Rect();
// 				start_button->x = 286;
// 				start_button->y = 132;
// 				start_button->w = 208;
// 				start_button->h = 57;
// 				SDL_RenderDrawRect(gRenderer, start_button);

// 				printf("Drawn Rectangle\n");
// 				//Handle events on queue
// 				while( SDL_PollEvent( &e ) != 0 )
// 				{
// 					//User requests quit
// 					if( e.type == SDL_QUIT )
// 					{
// 						quit = true;
// 					}
// 				}

// 				if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP){
// 					int x, y;
// 					SDL_GetMouseState(&x, &y);
// 					if(e.type == SDL_MOUSEBUTTONUP && check_click_in_rect(x,y,start_button)){
// 						start_screen = false;
// 					}
// 				}

//                 //Clear screen
// 				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
// 				SDL_RenderClear( gRenderer );

// 				if(start_screen){
// 					// SDL_BlitSurface( gStartSurface, NULL, gScreenSurface, NULL );
//                     startTexture.render(0, 0);
// 				}
// 				else{
// 					// SDL_BlitSurface( gGameSurface, NULL, gScreenSurface, NULL );
//                     gameTexture.render(0, 0);
// 				}
// 				//Update the surface
// 				//SDL_UpdateWindowSurface( gWindow );
// 				SDL_RenderPresent(gRenderer);
// 			}
// 		}
// 	}

// 	//Free resources and close SDL
// 	close();

// 	return 0;
// }