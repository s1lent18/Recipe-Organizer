#ifndef NODEFORLL_H
#define NODEFORLL_H
#include <iostream>
#include <string>
using namespace std;

class NodeforLL
{
public:
	string data;
	NodeforLL* next;

	NodeforLL()
	{
		data = "";
		next = NULL;
	};

	NodeforLL(string data)
	{
		this->data = data;
		next = NULL;
	}

};

#endif