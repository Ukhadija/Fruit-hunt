// Ume Khadija
//
// i210427@nu.edu.pk
//
//////////
#pragma once
#include <iostream>
#include<string>
#include <fstream>
using namespace std;

#ifndef QUEUE_H
#define QUEUE_H

template <class T>
struct Node
{
	T data;
	Node <T>* next;
	Node(T d)
	{
		data = d;
		next = NULL;
	}
};

template <class T>
class Queue {
private:
	Node<T>* front;
	Node<T>* rear;
	int const totalSize = 4;
	int currSize;
public:
	Queue()
	{
		//totalSize = 4;
		front = rear = NULL;
		currSize = 0;
	}

	void enqueue(T d)
	{
		if (currSize < 4)
		{
			Node<T>* temp = new Node<T>(d);
			if (front == NULL)
			{
				front = temp;
				rear = temp;
			}
			else
			{
				Node<T>* temp1 = rear;
				temp1->next = temp;
				temp->next = NULL;
				rear = temp;
			}
			currSize++;

		}
	}

	void dequeue()
	{
		if (front != NULL)
		{
			Node <T>* temp = front;
			front = front->next;
			delete temp;
			currSize--;
		}
	}
	bool checkData(T d)
	{
		bool flag = false;
		Node<T>* temp = front;
		while (temp != NULL)
		{
			if (temp->data == d)
			{
				flag = true;
			}
			temp = temp->next;
		}
		return flag;
	}
	T Front()
	{
		
		return front->data;
	
	}

	int getSize()
	{
		return currSize;
	}
	bool isEmpty()
	{
		if (front == NULL)
		{
			return true;
		}
		return false;
	}

	void Display()
	{
		Node<T>* p = front;
		while (p != NULL)
		{
			cout << p->data << " ";
			p = p->next;

		}
		cout << endl;
	}

};

#endif // !QUEUE_H
