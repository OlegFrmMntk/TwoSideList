#include "pch.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <stdio.h>
using namespace std;

template <typename T>
class List
{
public:
	List();
	~List();

	void push_front(T data);
	void push_back(T data);
	
	int get_front();
	int get_back();

	void pop_front();
	void pop_back();
	
	void clear();

	void PrintFromHead();
	void PrintFromTail();

	int GetSize() { return Size; }
	T& operator[](const int index);

private:

	template <typename T>
	class Node
	{
	public:
		Node *pPrev, *pNext;
		T data;

		Node(T data = T(), Node *pPrev = nullptr, Node *pNext = nullptr)
		{
			this->data = data;
			this->pPrev = pPrev;
			this->pNext = pNext;
		}
	};

	int Size;
	Node<T> *head, *tail;
};

template <typename T>
List<T>::List()
{
	Size = 0;
	head = nullptr;
	tail = nullptr;
}

template<typename T>
List<T>::~List()
{
	clear();
}

template<typename T>
void List<T>::clear()
{
	while (Size)
	{
		pop_front();
	}
}

template<typename T>
void List<T>::PrintFromHead()
{
	Node<T> *print = head;
	while (print)
	{
		cout << print->data << " ";
		print = print->pNext;
	}
	cout << endl;
}

template<typename T>
void List<T>::PrintFromTail()
{

	while (Size)
	{
		cout << get_back() << " ";
	}

	cout << endl;
}

template<typename T>
void List<T>::pop_front()
{
	Node<T> *temp = head;
	
	if (Size > 1)
	{
		head = head->pNext;
	}
	else
		tail = head = head->pNext;

	delete temp;

	Size--;
}

template<typename T>
void List<T>::pop_back()
{
	Node<T> *temp = tail;

	if (Size > 1)
	{
		tail = tail->pPrev;
	}
	else
		tail = head = head->pPrev;

	delete temp;

	Size--;
}

template<typename T>
void List<T>::push_front(T data)
{

	if (Size > 1)
	{
		Node<T> *temp = head;
		head = new Node <T>(data, nullptr, head);
		temp->pPrev = head;
	}
	else if (Size == 1)
	{
		head = new Node <T>(data, nullptr, head);
		tail->pPrev = this->head;
	}
	else
	{
		head = tail = new Node <T>(data, tail, head);
	}

	Size++;
}

template<typename T>
void List<T>::push_back(T data)
{

	if (Size > 1)
	{
		Node<T> *time = tail;
		tail = new Node<T>(data, tail, nullptr);
		time->pNext = tail;
	}
	else if (Size == 1)
	{
		tail = new Node<T>(data, tail, nullptr);
		head->pNext = this->tail;
	}
	else
	{
		head = tail = new Node<T>(data, tail, head);
	}

	Size++;
}

template<typename T>
int List<T>::get_front()
{
	Node<T> *temp = head;

	if (Size > 1)
	{
		head = head->pNext;
	}
	else
		tail = head = head->pNext;

	int x = temp->data;
	delete temp;

	Size--;
	return x;
}

template<typename T>
int List<T>::get_back()
{
	Node<T> *temp = tail;

	if (Size > 1)
	{
		tail = tail->pPrev;
	}
	else
		tail = head = head->pPrev;

	int x = temp->data;
	delete temp;

	Size--;
	return x;
}


template<typename T>
T & List<T>::operator[](const int index)
{
	int counter = 0;
	Node <T> *current = this->head;

	while (current != nullptr)
	{
		if (counter == index)
		{
			return current->data;
		}
		current = current->pNext;
		counter++;
	}
}


int main()
{
	setlocale(LC_ALL, "ru");

	List < int > spisok;
	
	int n;
	cout << "Введите количество элементов: ";
	cin >> n;
	cout << "Введите элементы списка:" << endl;

	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;
		spisok.push_back(x);
	}

	int mn = INT_MAX, mx = -INT_MAX;
	for (int i = 0; i < n; i++)
	{
		int x = spisok.get_front();

		mn = min(mn, x);
		mx = max(mx, x);

		spisok.push_back(x);
	}
	
	bool kl1 = false, kl2 = false;
	for (int i = 0; i < n; i++)
	{
		int x = spisok.get_front();

		if (mn == x && !kl1)
		{
			kl1 = true;
			spisok.push_back(mx);
		}
		else if (mx == x && !kl2)
		{
			kl2 = true;
			spisok.push_back(mn);
		}
		else spisok.push_back(x);
	}
	
	int Number;
	cout << "Введите вариант вывода списка:" << endl <<  "1)С начала" << endl << "2)С конца" << endl;
	cin >> Number;

	if (Number == 1) spisok.PrintFromHead();
	else spisok.PrintFromTail();

	return 0;
}