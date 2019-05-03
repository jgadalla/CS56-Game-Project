 #include <SDL2/SDL.h>
 #include <SDL2_image/SDL_image.h>
 #include <stdio.h>
 #include <cstdio>
 #include <cstdlib>
 #include <ctime>
 #include <iostream>
 #include "Car.hpp"
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

//booleans for stopping cars
 bool n_stop = false;
 bool e_stop = false;
 bool s_stop = false;
 bool w_stop = false;

 bool startGame = false;

 bool init();
 bool loadMedia();
 void close();

 SDL_Window* gWindow = NULL;
 SDL_Renderer* gRenderer = NULL;

 //screen textures 
 LTexture startTexture;
 LTexture gameTexture;
 LTexture carTexture_B;
 LTexture carTexture_Y;
 LTexture carTexture_R;
 LTexture carTexture_Bl;

 

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
       if( !loadMedia() ){
       printf( "Failed to load media!\n" );
       }
       else{

       //Main loop flag
	   bool start_screen = true;
       bool quit = false;      

	   //Event handler	
       SDL_Event e;    

	   //Current animation frame                        
       long int frame = 1;                     
  

       /* initialize random seed: */
       srand (time(NULL));

       /* generate secret number between 1 and 10: */
       int random = 0;

        //queue for cars from different directions
       Queue objectList;  
       Queue objectListS;
       Queue objectListE;
       Queue objectListW;

       //Unit* plane = new Unit(&carTexture, 0, (float)SCREEN_HEIGHT/2);
       Unit* car = NULL;
       //Unit* bullet = NULL;

	   //While application is running
       while( !quit )                          
         {
           if(frame%240 == 0)
                 {
		   
		   switch (rand()%4)
		   {
			//black   
		   case 0:
			   car = new Car(&carTexture_Bl, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
			   break;
			//red   
		   case 1:
			   car = new Car(&carTexture_R, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
			   break;
			//yellow
		   case 2:
			   car = new Car(&carTexture_Y, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
			   break;
			//blue   
		   case 3:
			   car = new Car(&carTexture_B,(float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
			   break;	   
		   //default -- red car 
		   default:
			   car = new Car(&carTexture_R,(float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
			   break;
		   }

           objectList.Enqueue(car);
      }


          // this code does not show a button on the screen
          // change needed here
          SDL_Rect* start_button = new SDL_Rect();
          start_button->x = 286;
          start_button->y = 132;
          start_button->w = 208;
          start_button->h = 57;
          SDL_RenderDrawRect(gRenderer, start_button);

		   //Handle events on queue
           while( SDL_PollEvent( &e ) != 0 )   
         {

           //User requests quit   -- Important for ending game 
           if( e.type == SDL_QUIT )
             {
               quit = true;
             }

         if(e.type == SDL_KEYDOWN){
			  switch (e.key.keysym.sym)
			  {
			  case SDLK_d:
				  e_stop = !e_stop;
				  break;
			  case SDLK_a:
				  w_stop = !w_stop;
				  break;
			  case SDLK_w:
				  n_stop = !n_stop;
				  break;
			  case SDLK_s:
				  s_stop = !s_stop;
				  break;	  	  	  
			   default:
			 	  break;
			    }
		    }	

         }

         if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP){
					int x, y;
					SDL_GetMouseState(&x, &y);
					if(e.type == SDL_MOUSEBUTTONUP && check_click_in_rect(x,y,start_button)){
						start_screen = false;
            
					}
				}

           SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );    //Clear screen
           SDL_RenderClear( gRenderer );

          if(start_screen){
            startTexture.Render(0, 0, gRenderer);
          }
          else{
            gameTexture.Render(0, 0, gRenderer);
            objectList.Render(gRenderer);
            objectList.Move(n_stop, e_stop, s_stop, w_stop);
          }

		  if(start_screen == false) {
			  frame++; 
		   }

          objectList.Clean();
          SDL_RenderPresent( gRenderer );     //Update screen
		  
         }

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
       gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, 
	   					SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, 
						   SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
       if( gWindow == NULL )
     {
       printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
       success = false;
     }
       else
     {
       //Create renderer for window
       gRenderer = SDL_CreateRenderer( gWindow, -1, 
	   					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
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

   //Load  texture

  if( !startTexture.LoadFromFile( "Images/Start-Screen.png", gRenderer ) )
	{
		printf( "Failed to load Foo' texture image!\n" );
		success = false;
	}

  if( !carTexture_R.LoadFromFile( "Images/red.png", gRenderer ) )
	{
		printf( "Failed to load Foo' texture image!\n" );
		success = false;
	}

	if( !carTexture_Bl.LoadFromFile( "Images/black.png", gRenderer ) )
	{
		printf( "Failed to load Foo' texture image!\n" );
		success = false;
	}

	if( !carTexture_Y.LoadFromFile( "Images/yellow.png", gRenderer ) )
	{
		printf( "Failed to load Foo' texture image!\n" );
		success = false;
	}

	if( !carTexture_B.LoadFromFile( "Images/blue.png", gRenderer ) )
	{
		printf( "Failed to load Foo' texture image!\n" );
		success = false;
	}
	
	if( !gameTexture.LoadFromFile( "Images/roadT.png", gRenderer ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}

   return success;
 }

 void close()
 {
   //Free loaded images
   gameTexture.Free();
   startTexture.Free();
   carTexture_B.Free();
   carTexture_Bl.Free();
   carTexture_Y.Free();
   carTexture_R.Free();

   //Destroy window
   SDL_DestroyRenderer( gRenderer );
   SDL_DestroyWindow( gWindow );
   gWindow = NULL;
   gRenderer = NULL;

   //Quit SDL subsystems
   IMG_Quit();
   SDL_Quit();
 }

