#include <iostream>
#include <string>

using namespace std;

struct Student
{
	string Name;
	string ID;
	float Point;

	bool operator < (Student b)
	{
		return Point < b.Point;
	}

	bool operator > (Student b)
	{
		return Point > b.Point;
	}
};

ostream& operator <<(ostream& output, Student a)
{
	output << a.Name << "-" << a.ID << "-" << a.Point;
	return output;
}

template <class T>
struct Node
{
	T Data;
	Node* next;
};

template <class T>
Node<T>* getNode(T k)
{
	Node<T>* p = new Node<T>;
	
	if (p == nullptr) return nullptr;
	p->Data = k;
	p->next = nullptr;
	return p;
}

template <class T>
bool increase(T a, T b)
{
	return a < b;
}

template <class T>
bool decrease(T a, T b)
{
	return a > b;
}

template <class T>
void MakeOrderedList(Node<T>* h, T k, bool (*condition)(T, T))
{
	Node<T>* p1 = h;
	Node<T>* p2 = p1->next;

	while (p2 && condition(p2->Data, k))
	{
		p1 = p2;
		p2 = p1->next;
	}

	Node<T>* p = getNode(k);
	p1->next = p; 
	p->next = p2;
}

template <class T>
void destroyList(Node<T>* Head)
{
	if (Head == nullptr) return;

	Node<T>* tmp = nullptr;
	while (Head != nullptr)
	{
		tmp = Head;
		Head = Head->next;
		free(tmp);
	}
}

template<class T>
void printList(Node<T>* head)
{
	for (Node<T>* i = head->next; i != nullptr; i = i->next)
	{
		cout << i->Data << ' ';
	}
}

void Input(Node<int>*& head, bool (*condition)(int , int))
{
	int tmp;
	while (1)
	{
		cout << "Enter next data: ";
		cin >> tmp;
		if (tmp == 0) return;	
		MakeOrderedList<int>(head, tmp, condition);
		printList(head);
		cout << "\n";
	}
}

void Input(Node<string>*& head, bool (*condition)(string, string))
{
	string tmp;
	while (1)
	{
		cout << "Enter next data: ";
		getline(cin, tmp);
		if (tmp == "0") return;
		MakeOrderedList<string>(head, tmp, condition);
		printList(head);
		cout << "\n";
	}
}

void Input(Node<Student>*& head, bool (*condition)(Student, Student))
{
	Student tmp;
	while (1)
	{
		cout << "Enter name: ";
		getline(cin, tmp.Name);
		if (tmp.Name == "0") return;
		cout << "Enter ID: ";
		getline(cin, tmp.ID);
		cout << "Enter point: ";
		cin >> tmp.Point;
		cin.ignore();

		MakeOrderedList<Student>(head, tmp, condition);
		printList(head);
		cout << "\n";
	}
}

int main(void)
{
	//Node<int>* head = new Node<int>;
	//Node<string>* head = new Node<string>;
	Node<Student>* head = new Node<Student>;
	if (head == nullptr) return 0;
	head->next = nullptr;
	Input(head, increase);
	//Input(head, decrease);
	destroyList(head);
}
