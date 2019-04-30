// #pragma once
// #include "Node.hpp"

// class Queue{
	
// public:
// 	Queue();
// 	~Queue();
// 	void Render();
// 	void Move();
// 	void Enqueue();
// 	void Dequeue();
// 	void clean();
// private:
// 	Node* head_;
// 	Node* tail_;

// };

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
    void Render(long int& frame, SDL_Renderer* gRenderer, bool debug);
    void Render(SDL_Renderer* gRenderer);
    void Move();
};
