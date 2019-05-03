#include"Enemy.hpp"

Enemy::Enemy()
{

}

Enemy::~Enemy()
{
  cout<<"Enemy Deallocated"<<endl;
}

Enemy::Enemy(LTexture* image, float x, float y):Unit(image, x, y)
{
  spriteSheetTexture = image;
  this->width = image->GetWidth();
  this->height = image->GetHeight();
}


void Enemy::Move()
{
  //speedx = speedx * friction;
  //speedy = speedy * friction;

  //x = x + speedx;
  y = y + 1; //speedy;
  if(y > 900)
    {
      SetAlive(false);
    }
}

void Enemy::Render(SDL_Renderer* gRender)
{
  spriteSheetTexture->Render(x, y, gRender);
}