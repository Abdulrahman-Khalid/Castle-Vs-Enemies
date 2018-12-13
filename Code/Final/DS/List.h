#pragma once
struct Node {
	int KTS;
	int S;
	int FD;
	int KD;
	Node* Next;
};
class List
{
	Node* Head;
	Node* Tail;
	int counter;
	/*Node * MergeSort(Node * my_node);
	Node * Merge(Node * firstNode, Node * secondNode);
	Node * Split(Node * my_node);*/
	void Split(Node * head, Node ** front, Node ** back);
	Node * MergeLists(Node * H1, Node * H2);
	void MergeSort(Node ** source);
public:
	List();
	void add(int kts, int s, int fd, int kd);
	void connect(List & L);
	void GetToPrint(int &kts, int &s, int &fd, int &kd);
	void destruct();
	int GetCounter() const;
	float GetavgFD_KD(float & avgKD);
	void BeforeGetToPrint();
	void Sort();
	~List();
};
