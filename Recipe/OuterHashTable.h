#ifndef OUTERHASHTABLE_H
#define OUTERHASHTABLE_H
#include <iostream>
#include <string>
#include <vector>
#include "OuterNode.cpp"
using namespace std;

class OuterHashTable
{
public:
	OuterNode** table = new OuterNode * [26]{ NULL };

	OuterHashTable()
	{
		for (int i = 0; i < 26; i++)
		{
			table[i] = NULL;
		}
	}

	int Hash(string name)
	{
		return (name[0] % 65);
	}

	void append(int index, string recipename, LinkedList* Ing, LinkedList* Ins, string cuisname, string foodtype)
	{
		int i = Hash(cuisname);

		OuterNode* n = new OuterNode(cuisname, recipename, Ins, Ing, index, foodtype);

		if (table[i] == NULL)
		{
			table[i] = n;
		}
		else
		{
			OuterNode* temp = table[i];

			if (temp->cuisinename == cuisname)
			{
				goto update;
			}

			while (temp->next != NULL)
			{
				if (temp->cuisinename == cuisname)
				{
				update:
					temp->type[index]->append(recipename, Ins, Ing, foodtype);

					return;
				}
				else if (temp->next->cuisinename == cuisname)
				{
					temp->next->type[index]->append(recipename, Ins, Ing, foodtype);

					return;
				}
				temp = temp->next;
			}

			temp->next = n;
		}
	}

	LinkedList* getcuisnames()
	{
		LinkedList* names = new LinkedList();

		for (int i = 0; i < 26; i++)
		{
			OuterNode* temp = table[i];

			if (temp != NULL)
			{
				while (temp != NULL)
				{
					names->append(temp->cuisinename);

					temp = temp->next;
				}
			}
		}

		return names;
	}

	vector<vector<vector<string>>> getspecficcuisrecipes()
	{
		vector<string> recipe;
		vector<vector<string>> type;
		vector<vector<vector<string>>> cuis;

		for (int i = 0; i < 26; i++)
		{
			OuterNode* temp = table[i];

			if (temp != NULL)
			{
				while (temp != NULL)
				{
					recipe.clear();
					for (int j = 0; j < 4; j++)
					{
						recipe = temp->type[j]->getrecipename();
						type.push_back(recipe);
					}
					cuis.push_back(type);
					type.clear();
					temp = temp->next;
				}
			}
		}
		return cuis;
	}

	void fulldisplay()
	{
		for (int i = 0; i < 26; i++)
		{
			OuterNode* temp = table[i];

			if (temp != NULL)
			{
				while (temp != NULL)
				{
					cout << temp->cuisinename << ": " << endl;

					for (int j = 0; j < 4; j++)
					{
						temp->type[j]->display();
					}

					temp = temp->next;
				}
			}
		}
	}

	void checkdiplay()
	{
		for (int i = 0; i < 26; i++)
		{
			OuterNode* temp = table[i];

			if (temp != NULL)
			{
				while (temp != NULL)
				{
					cout << temp->cuisinename << ": " << endl;

					for (int j = 0; j < 4; j++)
					{
						temp->type[j]->copy();
						cout << endl;
					}

					temp = temp->next;
				}
			}
		}
	}

	NodeforHash* SearchSpecific(string rname) 
	{
		for (int i = 0; i < 26; i++) 
		{
			OuterNode * temp = table[i];

			while (temp != NULL) 
			{
				for (int j = 0; j < 4; j++) 
				{
					HashTable * temp2 = temp->type[j];

					if (temp2 != NULL) 
					{
						int tempHash = temp2->hashformula(rname);

						NodeforHash * temp3 = temp2->Table[tempHash];

						while (temp3 != NULL) 
						{
							if (temp3->recipename == rname) 
							{
								NodeforHash* forReturn = new NodeforHash();
								forReturn->recipename = temp3->recipename;
								forReturn->Ingredients = temp3->Ingredients;
								forReturn->Instructions = temp3->Instructions;
								return forReturn;
							}
							temp3 = temp3->next;
						}
					}
				} 
				temp = temp->next;
			}
		}
		return NULL;
	}

	vector <string> getalltherecipenames()
	{
		vector <string> recipenames;

		for (int i = 0; i < 26; i++)
		{
			OuterNode* temp = table[i];

			if (temp != NULL)
			{
				while (temp != NULL)
				{
					for (int j = 0; j < 4; j++)
					{
						for (int k = 0; k < 26; k++)
						{
							NodeforHash* temp2 = temp->type[j]->Table[k];

							if (temp2 != NULL)
							{
								while (temp2 != NULL)
								{
									recipenames.push_back(temp2->recipename);

									temp2 = temp2->next;
								}
							}
						}
					}
					temp = temp->next;
				}
			}
		}
		
		return recipenames;
	}
};
#endif