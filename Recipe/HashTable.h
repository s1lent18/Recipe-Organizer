#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <string>
#include <vector>
#include "NodeforHash.cpp"
using namespace std;

class HashTable
{
public:
	NodeforHash** Table = new NodeforHash * [26]{ NULL };

	HashTable()
	{

	};

	int hashformula(string recipename)
	{
		return (recipename[0] % 65);
	}

	void append(string recipename, LinkedList* Ins, LinkedList* Ing, string foodtype)
	{
		NodeforHash* n = new NodeforHash(Ins, Ing, recipename, foodtype);

		int index = hashformula(recipename);

		if (Table[index] == NULL)
		{
			Table[index] = n;
		}
		else
		{
			NodeforHash* temp = Table[index];

			while (temp->next != NULL)
			{
				temp = temp->next;
			}

			temp->next = n;
		}
	}

	void search(string recipename)               
	{
		int index = hashformula(recipename);

		bool found = false;

		NodeforHash* temp = Table[index];

		while (temp != NULL)
		{
			if (temp->recipename == recipename)
			{
				found = 1;

				break;
			}
			temp = temp->next;
		}
		return;
	}

	void displayspecific(string rname)
	{
		int index = hashformula(rname);

		NodeforHash* temp = Table[index];

		if (temp == NULL)
		{
			return;
		}
		else
		{
			while (temp != NULL)
			{
				if (temp->recipename == rname)
				{
					cout << temp->recipename << endl;

					temp->Ingredients->display();

					temp->Instructions->display();
				}
				temp = temp->next;
			}
			cout << "Recipe not found" << endl;
		}
	}

	void display()
	{
		for (int i = 0; i < 26; i++)
		{
			NodeforHash* temp = Table[i];

			if (temp != NULL)
			{
				while (temp != NULL)
				{
					cout << temp->foodtype << endl;

					cout << temp->recipename << endl;

					temp->Ingredients->display();

					temp->Instructions->display();

					cout << endl;

					temp = temp->next;
				}
			}
		}
	}

	void copy()
	{
		for (int i = 0; i < 26; i++)
		{
			NodeforHash* temp = Table[i];

			if (temp != NULL)
			{
				while (temp != NULL)
				{
					cout << temp->recipename;

					temp = temp->next;
				}
			}
		}
	}

	vector<string> getrecipename()
	{
		vector <string> names;

		for (int i = 0; i < 26; i++)
		{
			NodeforHash* temp = Table[i];

			if (temp != NULL)
			{
				while (temp != NULL)
				{
					names.push_back(temp->recipename);

					temp = temp->next;
				}
			}
		}
		return names;
	}
};
#endif