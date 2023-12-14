#ifndef OUTERNODE_H
#define OUTERNODE_H
#include <iostream>
#include <string>
#include <vector>
#include "HashTable.cpp"
using namespace std;

class OuterNode
{
public:
	string cuisinename;
	HashTable** type = new HashTable * [4]{ NULL };
	OuterNode* next;

	OuterNode()
	{
		cuisinename = "";
		next = NULL;
	}

	OuterNode(string cuisinename, string rname, LinkedList* Ins, LinkedList* Ing, int index, string foodtype)
	{
		this->cuisinename = cuisinename;

		for (int i = 0; i < 4; i++)
		{
			type[i] = new HashTable();
		}

		type[index]->append(rname, Ins, Ing, foodtype);
		next = NULL;
	}
};
#endif