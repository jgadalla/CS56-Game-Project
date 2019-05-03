#pragma once
#include "Node.hpp"

class Queue
  {
  private:
    Node* head;
    Node* tail;
  public:
    Queue();
    ~Queue();
    //add unit to queue
    void Enqueue(Unit*);  
    //remove unit of the screen 
    void Clean();			

	//render objects in the list
    void Render(SDL_Renderer* gRenderer);
	//move objects in the list
    void Move(bool n_stop, bool e_stop, bool s_stop, bool w_stop);
};
