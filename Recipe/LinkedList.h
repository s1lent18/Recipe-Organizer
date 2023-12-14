#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include <string>
#include "NodeforLL.cpp"
using namespace std;

class LinkedList
{
public:
	NodeforLL* head;
	NodeforLL* tail;

	LinkedList()
	{
		head = NULL;
		tail = NULL;
	}

	void append(string str)
	{
		NodeforLL* n = new NodeforLL(str);

		if (head == NULL)
		{
			head = n;

			tail = n;
		}
		else
		{
			tail->next = n;

			tail = n;
		}
	}

	void deleteattail()
	{
		if (head == NULL)
		{
			return;
		}
		if (head->next == NULL)
		{
			head = NULL;
		}

		NodeforLL* temp = head;

		while (temp->next->next != NULL)
		{
			temp = temp->next;
		}

		temp->next = NULL;

		delete temp->next;
	}

	void deletefullLL()
	{
		while (head != NULL)
		{
			NodeforLL* temp = head->next;

			delete head;

			head = temp;
		}
	}
	void display()
	{
		NodeforLL* temp = head;

		if (temp == NULL)
		{
			cout << "LinkedList empty" << endl;
		}

		while (temp != NULL)
		{
			cout << temp->data << endl;
			temp = temp->next;
		}

	}

};

#endif