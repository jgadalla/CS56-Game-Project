// #pragma once
// #include "Node.hpp"

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
    void Enqueue(Unit*);
    void Clean();
    void Render(SDL_Renderer* gRenderer, bool debug);
    void Render(SDL_Renderer* gRenderer);
    void Move();
    void setKey();
};
