#include"Car.hpp"

Car::Car(){}

float Car::getStartX(){
    return startPositionX;
}

float Car::getStartY(){
    return startPositionY;
}

Car::~Car()
{
  cout<<"Car Deallocated"<<endl;
}

Car::Car(LTexture* image, float x, float y):Unit(image, x, y)
{

  //generate random dir
    switch (rand() % 4)
    {
    //east   
    case 1:
        startPositionX = x + 10;
        startPositionY = y/2 - 40;
        dir = 90;
        this->x = startPositionX;
        this->y = startPositionY;
        break;
    //south
    case 2:
        startPositionX = x/2 + 10;
        startPositionY = y + 10;
        dir = 180;
        this->x = startPositionX;
        this->y = startPositionY;
        break;
    //west   
    case 3:
        startPositionX = 0 - 30;
        startPositionY = y/2 + 5;
        dir = -90;
        this->x = startPositionX;
        this->y = startPositionY;
        break;	   
    //north
    default:
        startPositionX = x/2 - 35;
        startPositionY = 0 - 30; 
        dir = 0;
        this->x = startPositionX;
        this->y = startPositionY;
        break;
    }


  spriteSheetTexture = image;
  this->width = image->GetWidth();
  this->height = image->GetHeight();

}


void Car::Move(bool n_stop, bool e_stop, bool s_stop, bool w_stop)
{
    switch (dir)
    {
    //east   
    case 90:
        if(e_stop == false){
            x = x - 1;
            if(x < -50){
                SetAlive(false); // could use this to track score or on clean function 
            }
        }else{
            if(x < 692){
                x = x - 1;
                if(x < -50){
                    SetAlive(false); // could use this to track score or on clean function
                }
            }else{
                if(x > 692){
                    if(front == false){
                        x = x - 1;
                    }else{
                        if(x == startPositionX){
                            std::cout << "east road full"; 
                        }
                    }      
                }
            }   
        }
        break;
    //south
    case 180:
        if(s_stop == false){
            y = y - 1;
            if(y < -50){
                SetAlive(false);
            }
        }else{
            if(y < 458){
                y = y - 1;
                if(y < -50){
                    SetAlive(false);
                }
            }else{
                if(y > 458){
                    if(front == false){
                        y = y - 1;
                    }else{
                        if(y == startPositionY){
                            std::cout << "south road full"; 
                        }
                    }
                }
                
            }
        }
        break;
    //west   
    case -90:
        if(w_stop == false){
            x = x + 1;
            if(x > 1130){
                SetAlive(false);
            }
        }else{
            if(x > 370){
                x = x + 1;
                if(x > 1130){
                    SetAlive(false);
                }
            }else{
                if(x < 370){
                    if(front == false){
                        x = x + 1;
                    }else{
                        if(x == startPositionX){
                            std::cout << "west road full"; 
                        }
                    }
                }
            }
        }
        
        break;	   
    //north
    default:
        if(n_stop == false){
            y = y + 1; 
            if(y > 690) {
                SetAlive(false);
            }
        }else{
            if(y > 142){
                y = y + 1;
                if(y < 690){
                    SetAlive(false);
                }
            }else{
                if(y < 142){
                    if(front == false){
                        y = y + 1;
                    }else{
                        if(y == startPositionY){
                            std::cout << "north road full"; 
                        }
                    }
                }
            }
        }    
        break;
    }
}


void Car::Render(SDL_Renderer* gRender)
{
  spriteSheetTexture->Render(x, y, gRender, dir);
}