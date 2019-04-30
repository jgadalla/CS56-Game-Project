#include "Unit.hpp"

Unit::Unit()
{

}

Unit::Unit(LTexture* image, float x, float y)
{
  spriteSheetTexture = image;


  // //Frame 0
  // spriteClips[ 0 ].x =   0;
  // spriteClips[ 0 ].y =   0;
  // spriteClips[ 0 ].w = 128;
  // spriteClips[ 0 ].h = 96;

  // //Frame 1
  // spriteClips[ 1 ].x = 128;
  // spriteClips[ 1 ].y =   0;
  // spriteClips[ 1 ].w = 128;
  // spriteClips[ 1 ].h = 96;

  // //Frame 2
  // spriteClips[ 2 ].x = 256;
  // spriteClips[ 2 ].y = 0;
  // spriteClips[ 2 ].w = 128;
  // spriteClips[ 2 ].h = 96;

  this->x = x;
  this->y = y;

  // this->width = spriteClips[ 0 ].w;
  // this->height = spriteClips[ 0 ].h;

  this->width = image->GetWidth();
  this->height = image->GetHeight();

  friction = 0.95f;
  speedx = 0;
  speedy = 0;
  alive  = true;
}


Unit::~Unit()
{
  spriteSheetTexture = NULL;
}

void Unit::SetAlive(bool alive)
{
  this->alive = alive;
}

bool Unit::GetAlive()
{
  return alive;
}

void Unit::Move(int direction)
{

  if(direction==LEFT)
    {
      speedx = -5;
      x+=speedx;
    }

  if(direction==RIGHT)
    {
      speedx = 5;
      x+=speedx;
    }

  if(direction==UP)
    {
      speedy = -5;
      y+=speedy;
    }

  if(direction==DOWN)
    {
      speedy = 5;
      y+=speedy;
    }

}

void Unit::Move()
{
  speedx = speedx * friction;
  speedy = speedy * friction;

  x = x + speedx;
  y = y + speedy;
}

void Unit::Render(long int& frame, SDL_Renderer* gRenderer, bool debug)
{
  spriteSheetTexture->Render( x - width/2, y - height/2, &spriteClips[ frame % FLYING_FRAMES ], 0.0, NULL, SDL_FLIP_NONE, gRenderer );
  if(debug == true)
    {
      SDL_Rect rect = { x - width/2, y - height/2, width, height };
      SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
      SDL_RenderDrawRect( gRenderer, &rect );
    }
}

void Unit::Render(SDL_Renderer* gRenderer )
{
	//Set rendering space and render to screen
  spriteSheetTexture->Render(x, y, gRenderer);
	// SDL_Rect renderQuad = { x, y, width, height };
	// SDL_RenderCopy( gRenderer, texture, NULL, &renderQuad );
}


int Unit::GetWidth()
{
  return width;
}

int Unit::GetHeight()
{
  return height;
}

float Unit::GetX()
{
  return x;
}
float Unit::GetY()
{
  return y;
}
