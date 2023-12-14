#ifndef NODEFORHASH_H
#define NODEFORHASH_H
#include <iostream>
#include <string>
#include "LinkedList.cpp"
using namespace std;

class NodeforHash
{
public:
	const int size = 26;
	string recipename;
	string foodtype;
	LinkedList* Instructions;
	LinkedList* Ingredients;
	NodeforHash* next;


	NodeforHash()
	{
		recipename = "";
		next = NULL;
	};

	NodeforHash(LinkedList* Instructions, LinkedList* Ingredients, string recipename, string foodtype)
	{
		this->recipename = recipename;
		this->Ingredients = Ingredients;
		this->Instructions = Instructions;
		this->foodtype = foodtype;
		next = NULL;
	}

};

#endif