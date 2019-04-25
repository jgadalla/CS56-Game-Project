#pragma once
#include "Node.hpp"

class Queue{
	
public:
	Queue();
	~Queue();
	void Render();
	void Move();
	void Enqueue();
	void Dequeue();
	void clean();
private:
	Node* head_;
	Node* tail_;

};