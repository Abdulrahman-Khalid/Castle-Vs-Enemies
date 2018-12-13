
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "..\Enemies\Enemy.h"


class Queue
{
private:
	struct Node
	{
		Node* Next;
		Enemy* En;
	};
	typedef struct Node* NodePtr;

	NodePtr Front;
	NodePtr Tail;

	int Counter;

public:
	Queue();
	bool CreateNode(Node*&, Enemy*);
	void destruct();
	bool Enqueue(Enemy*);
	bool Dequeue();
	bool IsEmpty();
	int QueueTop();
	Enemy* GetEn();
	int GetCounter() const;
};

#endif