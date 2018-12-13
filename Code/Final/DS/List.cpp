#include "List.h"

List::List()
{
	Head = nullptr;
	Tail = nullptr;
	counter = 0;
}

void List::add(int kts, int s, int fd, int kd)
{
	Node* AddedNode = new Node;
	AddedNode->KTS = kts;
	AddedNode->KD = kd;
	AddedNode->FD = fd;
	AddedNode->S = s;
	if (Head == nullptr) {
		Head = AddedNode;
		Tail = AddedNode;
		Tail->Next = nullptr;
	}
	else
	{
		AddedNode->Next = Head;
		Head = AddedNode;
	}
	counter++;
}

void List::connect(List & L)
{
	if (Head == nullptr) {
		Head = L.Head;
		Tail = L.Tail;
		counter = L.counter;
	}
	else if (L.Tail != nullptr) {
		Tail->Next = L.Head;
		Tail = L.Tail;
		counter += L.counter;
	}
}

void List::GetToPrint(int & kts, int & s, int & fd, int & kd)
{
	if (Tail != nullptr) {
		kts = Tail->KTS;
		s = Tail->S;
		fd = Tail->FD;
		kd = Tail->KD;
		Tail = Tail->Next;
	}
}

void List::destruct()
{
	Node* DeletedNode = Head;
	while (Head != nullptr) {
		Head = Head->Next;
		delete DeletedNode;
		DeletedNode = Head;
	}
	Head = nullptr;
	Tail = nullptr;
}

int List::GetCounter() const
{
	return counter;
}

float List::GetavgFD_KD(float& avgKD)
{
	avgKD = 0;
	float avgFD = 0;
	Node* curr = Head;
	while (curr != nullptr) {
		avgFD += curr->FD;
		avgKD += curr->KD;
		curr = curr->Next;
	}
	avgFD /= counter;
	avgKD /= counter;
	return avgFD;
}

void List::BeforeGetToPrint()
{
	Tail = Head;
}

void List::Sort()
{
	if (Head == nullptr)
	{
		return;
	}
	MergeSort(&Head);
	while (Tail->Next != nullptr)
	{
		Tail = Tail->Next;
	}
}

void List::Split(Node* head, Node**front, Node**back)
{
	Node* fast;
	Node* slow;
	if (head == nullptr || head->Next == nullptr) 
	{
		*front = head; // &H1
		*back = nullptr; // &H2
	}
	else 
	{
		slow = head;
		fast = head->Next;
		while (fast != nullptr)
		{
			fast = fast->Next;
			if (fast != nullptr) 
			{
				slow = slow->Next;
				fast = fast->Next;
			}
		}
		*front = head; // H1
		*back = slow->Next; // H2
		slow->Next = nullptr;
	}
}

Node* List::MergeLists(Node* H1, Node* H2)
{
	Node* mergedList = nullptr;
	if (H1 == nullptr) {
		return H2;
	}
	else if (H2 == nullptr) {
		return H1;
	}
	if (H1->FD <= H2->FD)
	{
		mergedList = H1;
		mergedList->Next = MergeLists(H1->Next, H2);
	}
	else {
		mergedList = H2;
		mergedList->Next = MergeLists(H1, H2->Next);
	}
	return mergedList;
}

void List::MergeSort(Node**source)
{
	Node* head = *source;
	Node* H1 = nullptr;
	Node* H2 = nullptr;
	if (head == nullptr || head->Next == nullptr)
	{
		return;
	}
	Split(head, &H1, &H2);
	MergeSort(&H1);
	MergeSort(&H2);
	*source = MergeLists(H1, H2);
}

/*Node* List::MergeSort(Node *my_node)
{
	Node *secondNode;

	if (my_node == nullptr)
		return nullptr;
	else if (my_node->Next == nullptr)
		return my_node;
	else
	{
		secondNode = Split(my_node);
		return Merge(MergeSort(my_node), MergeSort(secondNode));
	}
}

Node* List::Merge(Node* firstNode, Node* secondNode)
{
	if (firstNode == nullptr) return secondNode;
	else if (secondNode == nullptr) return firstNode;
	else if (firstNode->FD <= secondNode->FD) //if I reverse the sign to >=, the behavior reverses
	{
		firstNode->Next = Merge(firstNode->Next, secondNode);
		return firstNode;
	}
	else
	{
		secondNode->Next = Merge(firstNode, secondNode->Next);
		return secondNode;
	}
}

Node* List::Split(Node* my_node)
{
	Node* secondNode;

	if (my_node == nullptr) return nullptr;
	else if (my_node->Next == nullptr) return nullptr;
	else {
		secondNode = my_node->Next;
		my_node->Next = secondNode->Next;
		secondNode->Next = Split(secondNode->Next);
		return secondNode;
	}
}*/

List::~List()
{
}