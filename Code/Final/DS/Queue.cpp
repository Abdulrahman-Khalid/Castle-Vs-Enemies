#ifndef _QUEUE_CPP_
#define _QUEUE_CPP_


#include <iostream>
#include "Queue.h"
using namespace std;



Queue::Queue()
{
	Front = Tail = NULL;
	Counter = 0;
}
///////////////////////////////////////////


int Queue::GetCounter() const
{
	return Counter;
}


bool Queue::CreateNode(Node*& n, Enemy* E)
{
	n = new Node;
	n->Next = NULL;
	n->En = E;
	return true;
}

void Queue::destruct()
{
	Node* DeletedNode = Front;
	while (Front != nullptr) {
		delete Front->En;                    //so important
		Front = Front->Next;
		delete DeletedNode;
		DeletedNode = Front;
	}
	Front = nullptr;
	Tail = nullptr;
}

bool Queue::Enqueue(Enemy* E)
{
	NodePtr n;
	CreateNode(n, E);
	Counter++;
	if (Front == NULL && Tail == NULL)
	{
		Front = Tail = n;
		return true;
	}
	else
	{
		Tail->Next = n;
		Tail = Tail->Next;
		return true;
	}
	return false;
}
/////////////////////////////////////////////



bool Queue::Dequeue()
{
	if (Counter == 0)
	{
		return false;
	}
	else
	{
		//Show_Front();
		Front = Front->Next;
		Counter--;
		if (Counter == 0)
		{
			Front = Tail = NULL;
		}
		return true;
	}
}

///////////////////////////////////////////////



bool Queue::IsEmpty()
{
	return (Counter == 0);
}
//////////////////////////////////////////////////



int Queue::QueueTop()
{
	return (Front->En)->GetArrivalTime();
}


Enemy* Queue::GetEn()
{
	return (Front->En);
}


#endif