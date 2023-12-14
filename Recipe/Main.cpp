#include <ctime>
#include <queue>
#include <thread>
#include <chrono>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include "OuterNode.cpp"
#include "HashTable.cpp"
#include "NodeforLL.cpp"
#include "HashTable.cpp"
#include "LinkedList.cpp"
#include <SFML/Audio.hpp>
#include "NodeforHash.cpp"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "OuterHashTable.cpp"
using namespace std;
using namespace sf;

int usercount = 0;
int currentcount = 2;

enum PageState
{
	mainpage,
	loginpage,
	greetingpage,
	recipeinput,
	recipeinput2,
	recipeinput3,
	recipesubmitted,
	askpage,
	appetizerpage,
	maincoursepage,
	dessertpage,
	drinkspage,
	flpage,
	recipepage,
	recipepage2,
	recipepage3,
	recipepage4,
	recipepage5,
	recipepage6,
	recipepage7,
	recipepage8,
	recipepage9,
	recipepage10,
	recipepage11,
	recipepage12,
	recipepage13,
	recipepage14,
	recipepage15,
	recipepage16,
	recipepage17,
	recipepage18,
	recipepage19,
	recipepage20,
	recipepage21,
	recipepage22,
	recipepage23,
	recipepage24,
	recipepage25,
	flrecipenamepage,
	recipeprintingpage,
	recipeprintingpage2,
	thankyou,
};

int getsize(LinkedList* N)
{
	int size = 0;

	NodeforLL* n = N->head;

	while (n != NULL)
	{
		size++;

		n = n->next;
	}

	return size;
}

void writefile(string user, string pass)
{
	fstream File;

	File.open("Credits.txt", ios::app);

	File.write(user.c_str(), user.size());

	File << endl;

	File.write(pass.c_str(), pass.size());

	File << endl << endl;

	File.close();
}

void fileinsertionpublic(queue <string> Q)
{
	ifstream FILE("Recipes.txt");

	LinkedList* system = new LinkedList();
	LinkedList* custom = new LinkedList();

	int checkcount = 0;

	bool flag = false;

	string line;

	if (FILE.is_open())
	{
		while (getline(FILE, line))
		{
			if (line == "#")
			{
				checkcount += 1;

				custom->append("#");
			}
			else if (checkcount >= 1)
			{
				custom->append(line);
			}
			else if (checkcount == 0)
			{
				system->append(line);
			}
		}

		custom->append("#");

		while (!Q.empty())
		{
			system->append(Q.front());

			Q.pop();
		}

		FILE.close();
	}

	ofstream OUTFILE("Recipes.txt", ios::out);

	if (OUTFILE.is_open())
	{
		NodeforLL* s = system->head;
		NodeforLL* c = custom->head;

		while (s != NULL)
		{
			OUTFILE << s->data << endl;

			s = s->next;
		}

		while (c != NULL)
		{
			OUTFILE << c->data << endl;

			c = c->next;
		}

		OUTFILE.close();
	}
}

vector <OuterHashTable*> readinput(OuterHashTable*& Final)
{
	ifstream FILE("Recipes.txt");

	vector <OuterHashTable*> privat;

	bool flag = false;

	string prev;

	string temp;

	if (FILE.is_open())
	{
		string tempcuis;
		string type;
		string rname;
		string ing;
		string ins;

		while (1)
		{
			if (FILE.eof())
			{
				break;
			}

			if (!flag)
			{
				getline(FILE, tempcuis);
			}
			else
			{
				tempcuis = prev;
			}

			getline(FILE, type);

			getline(FILE, rname);

			LinkedList* Ing = new LinkedList();
			LinkedList* Ins = new LinkedList();

			getline(FILE, ing);

			int ingcount = 0;

			for (int i = 0; i < ing.length(); i++)
			{
				if (ing[i] == '-')
				{
					temp += ' ';
				}
				else if (ing[i] == ' ')
				{
					Ing->append(temp);
					temp = "";
				}
				else
				{
					temp += ing[i];
				}
			}
			ingcount = 0;
			temp = "";

			getline(FILE, ins);

			for (int i = 0; i < ins.length(); i++)
			{
				if (ins[i] == '-')
				{
					temp += ' ';
				}
				else if (ins[i] == ' ')
				{
					Ins->append(temp);
					temp = "";
				}
				else if (ins[i] == ',')
				{

					Ins->append(temp);
					temp = "";
				}
				else
				{
					temp += ins[i];
				}
			}

			temp = "";

			if (type == "Appetizer")
			{
				Final->append(0, rname, Ing, Ins, tempcuis, "Appetizer");
			}
			else if (type == "Main-Course")
			{
				Final->append(1, rname, Ing, Ins, tempcuis, "Main-Course");
			}
			else if (type == "Dessert")
			{
				Final->append(2, rname, Ing, Ins, tempcuis, "Dessert");
			}
			else if (type == "Drinks")
			{
				Final->append(3, rname, Ing, Ins, tempcuis, "Drinks");
			}

			getline(FILE, temp);

			prev = temp;

			if (FILE.eof())
			{
				break;
			}
			else
			{
				if (temp == "#")
				{
					flag = false;

					break;
				}
				else
				{
					flag = true;
				}
			}
		}
		
		OuterHashTable* T = new OuterHashTable();

		while (!FILE.eof())
		{
			getline(FILE, temp);

			if (temp == "#")
			{
				privat.push_back(T);

				T = new OuterHashTable();
			}
			else
			{
				tempcuis = temp;

				getline(FILE, type);

				getline(FILE, rname);

				LinkedList* Ing = new LinkedList();

				LinkedList* Ins = new LinkedList();

				getline(FILE, ing);

				int ingcount = 0;

				temp = "";

				for (int i = 0; i < ing.length(); i++)
				{
					if (ing[i] == '-')
					{
						temp += ' ';
					}
					else if(ing[i] == ' ')
					{
						Ing->append(temp);

						temp = "";
					}
					else
					{
						temp += ing[i];
					}
				}

				ingcount = 0;

				temp = "";

				getline(FILE, ins);

				for (int i = 0; i < ins.length(); i++)
				{
					if (ins[i] == '-')
					{
						temp += ' ';
					}
					else if (ins[i] == ' ')
					{
						Ins->append(temp);

						temp = "";
					}
					else if (ins[i] == ',')
					{
						Ins->append(temp);
						temp = "";
					}
					else
					{
						temp += ins[i];
					}
				}

				temp = "";

				if (type == "Appetizer")
				{
					T->append(0, rname, Ing, Ins, tempcuis, "Appetizer");
				}
				else if (type == "Main-Course")
				{
					T->append(1, rname, Ing, Ins, tempcuis, "Main-Course");
				}
				else if (type == "Dessert")
				{
					T->append(2, rname, Ing, Ins, tempcuis, "Dessert");
				}
				else if (type == "Drinks")
				{
					T->append(3, rname, Ing, Ins, tempcuis, "Drinks");
				}
			}
		}
	
		FILE.close();
	}

	return privat;
}

void readfile(LinkedList* usernames, LinkedList* passwords)
{
	fstream File("Credits.txt");

	if (File.is_open())
	{
		string input;

		while (getline(File, input))
		{
			if (!input.empty())
			{
				usernames->append(input);
			}

			if (getline(File, input))
			{
				passwords->append(input);
			}
		}
		File.close();
	}
}

void fileinsertionprivate(queue <string> Q, int count, int n)
{
	ifstream FILE("Recipes.txt");

	LinkedList* system = new LinkedList();
	LinkedList* custom = new LinkedList();
	LinkedList* copy = new LinkedList();

	int checkcount = 0;

	string line;

	if (FILE.is_open())
	{
		while (getline(FILE, line))
		{
			if (line == "#")
			{
				checkcount++;
				custom->append("#");
			}
			else if (checkcount >= 1)
			{
				custom->append(line);
			}
			else if (checkcount == 0)
			{
				system->append(line);
			}
		}

		NodeforLL* temp = system->head;

		while (temp != NULL)
		{
			copy->append(temp->data);

			temp = temp->next;
		}

		temp = custom->head;

		int spacecount = 0;

		bool flag = false;

		while (temp != NULL)
		{
			if (temp->data == "#")
			{
				spacecount++;
			}
			else if (spacecount - 1 == count)
			{
				while (!Q.empty())
				{
					copy->append(Q.front());

					Q.pop();
				}
				if (count > n)
				{
					copy->append("#");
				}
			}

			copy->append(temp->data);

			temp = temp->next;
		}

		FILE.close();
	}

	ofstream OUTFILE("Recipes.txt", ios::out);

	if (OUTFILE.is_open())
	{
		NodeforLL* c = copy->head;

		while (c != NULL)
		{
			OUTFILE << c->data << endl;

			c = c->next;
		}

		OUTFILE.close();
	}
}

bool flagpass = false;
bool flaguser = false;
bool donerecipe = false;
bool wantpublic = false;
bool isingactive = false;
bool isinsactive = false;
bool wantprivate = false;
bool isdrinkactive = false;
bool isdessertactive = false;
bool typeselectionflag = false;
bool isappetizeractive = false;
bool isrecipenameactive = false;
bool ismaincourseactive = false;
bool isCuisinenameactive = false;

int main()
{
	srand(time(0));

	string flrecipename;

	vector <string> recipeIng;
	
	vector <string> recipeIns;
	
	vector <OuterHashTable* > priva;
	
	vector <string> namesfromthelinkedlist;
	
	vector <vector <string>> privatenames;
	
	OuterHashTable* input = new OuterHashTable();

	vector <vector <Text>> privatenamesfromcustom;

	priva = readinput(input);

	for (int i = 0; i < priva.size(); i++)
	{
		privatenames.push_back(priva[i]->getalltherecipenames());
	}
	
	LinkedList* NAMES = new LinkedList();

	NAMES = input->getcuisnames();

	NodeforLL* b = NAMES->head;

	RenderWindow window(VideoMode(600, 900), "DS-Project", Style::Titlebar | Style::Close);
	Event ev;

	Font font1;
	Font font2;
	Font font3;

	vector<vector<vector<string>>> alltherecipes;

	while (b != NULL)
	{
		namesfromthelinkedlist.push_back(b->data);
		b = b->next;
	}

	vector <Text> temperory;

	for (int i = 0; i < privatenames.size(); i++)
	{
		temperory.clear();

		for (int j = 0; j < privatenames[i].size(); j++)
		{
			Text t(privatenames[i][j], font3, 20);

			t.setFillColor(Color::Black);

			temperory.push_back(t);
		}

		privatenamesfromcustom.push_back(temperory);
	}

	alltherecipes = input->getspecficcuisrecipes();

	if (!font1.loadFromFile("C:/Users/jgpos/OneDrive/Desktop/Fonts/Pacifico-Regular.ttf"))
	{
		return EXIT_FAILURE;
	}

	if (!font2.loadFromFile("C:/Users/jgpos/OneDrive/Desktop/Fonts/Bahiana-Regular.ttf"))
	{
		return EXIT_FAILURE;
	}

	if (!font3.loadFromFile("C:/Users/jgpos/OneDrive/Desktop/Fonts/Handlee-Regular.ttf"))
	{
		return EXIT_FAILURE;
	}

	Texture texture1;
	if (!texture1.loadFromFile("C:/Users/jgpos/OneDrive/Desktop/Project-Images/CP.jpg"))
	{
		return EXIT_FAILURE;
	}

	Texture texture2;
	if (!texture2.loadFromFile("C:/Users/jgpos/OneDrive/Desktop/Project-Images/Inpput.jpg"))
	{
		return EXIT_FAILURE;
	}

	Texture texture3;
	if (!texture3.loadFromFile("C:/Users/jgpos/OneDrive/Desktop/Project-Images/Cover.jpg"))
	{
		return EXIT_FAILURE;
	}

	Texture texture4;
	if (!texture4.loadFromFile("C:/Users/jgpos/OneDrive/Desktop/Project-Images/Greeting.jpg"))
	{
		return EXIT_FAILURE;
	}

	Texture texture5;
	if (!texture5.loadFromFile("C:/Users/jgpos/OneDrive/Desktop/Project-Images/RecipePage.jpg"))
	{
		return EXIT_FAILURE;
	}

	Texture texture6;
	if (!texture6.loadFromFile("C:/Users/jgpos/OneDrive/Desktop/Project-Images/RecipePrint.jpg"))
	{
		return EXIT_FAILURE;
	}

	Texture texture7;
	if (!texture7.loadFromFile("C:/Users/jgpos/OneDrive/Desktop/Project-Images/AskPage.jpg"))
	{
		return EXIT_FAILURE;
	}
	
	Texture texture8;
	if (!texture8.loadFromFile("C:/Users/jgpos/OneDrive/Desktop/Project-Images/AppetizerPage.jpg"))
	{
		return EXIT_FAILURE;
	}
	
	Texture texture9;
	if (!texture9.loadFromFile("C:/Users/jgpos/OneDrive/Desktop/Project-Images/MainCoursePage.jpg"))
	{
		return EXIT_FAILURE;
	}
	
	Texture texture10;
	if (!texture10.loadFromFile("C:/Users/jgpos/OneDrive/Desktop/Project-Images/DessertPage.jpg"))
	{
		return EXIT_FAILURE;
	}

	Texture texture11;
	if (!texture11.loadFromFile("C:/Users/jgpos/OneDrive/Desktop/Project-Images/DrinksPage.jpg"))
	{
		return EXIT_FAILURE;
	}

	Texture texture12;
	if (!texture12.loadFromFile("C:/Users/jgpos/OneDrive/Desktop/Project-Images/RightArrow.png"))
	{
		return EXIT_FAILURE;
	}

	Texture texture13;
	if (!texture13.loadFromFile("C:/Users/jgpos/OneDrive/Desktop/Project-Images/LeftArrow.png"))
	{
		return EXIT_FAILURE;
	}

	Texture texture14;
	if (!texture14.loadFromFile("C:/Users/jgpos/OneDrive/Desktop/Project-Images/FL.jpg"))
	{
		return EXIT_FAILURE;
	}

	vector <Text> App;
	vector <Text> Main;
	vector <Text> Des;
	vector <Text> Dri;
	vector <Text> textvector;
	vector <Text> customiginput;
	vector <Text> customisinput;
	vector <vector <Text>> alldes;
	vector <vector <Text>> alldri;
	vector <vector <Text>> allapp;
	vector <vector <Text>> allmain;
	vector <Text> recipeprintingIng;
	vector <Text> recipeprintingIns;

	for (auto& j : namesfromthelinkedlist)
	{
		Text t(j, font3, 30);
		t.setFillColor(Color::Black);
		textvector.push_back(t);
	}

	for (int i = 0; i < alltherecipes.size(); i++)
	{
		App.clear();
		Main.clear();
		Des.clear();
		Dri.clear();

		for (int j = 0; j < alltherecipes[i].size(); j++)
		{
			for (int k = 0; k < alltherecipes[i][j].size(); k++)
			{
				if (j == 0)
				{
					Text appi(alltherecipes[i][j][k], font3, 15);
					appi.setFillColor(Color::Black);
					App.push_back(appi);
				}
				else if (j == 1)
				{
					Text main(alltherecipes[i][j][k], font3, 15);
					main.setFillColor(Color::Black);
					Main.push_back(main);
				}
				else if (j == 2)
				{
					Text des(alltherecipes[i][j][k], font3, 15);
					des.setFillColor(Color::Black);
					Des.push_back(des);
				}
				else if (j == 3)
				{
					Text dri(alltherecipes[i][j][k], font3, 15);
					dri.setFillColor(Color::Black);
					Dri.push_back(dri);
				}
			}
		}
		allapp.push_back(App);
		allmain.push_back(Main);
		alldes.push_back(Des);
		alldri.push_back(Dri);
	}

	float p1 = 230.f;
	float p2 = 255.f;
	float x1 = 175.f;
	float x2 = 310.f;

	float temp1 = p2;
	float temp2 = x2;
	float temp3 = 1.f;
	float temp4 = 1.f;

	for (int i = 0; i < textvector.size(); i++)
	{
		textvector[i].setPosition(p1, temp1);
	}

	for (int i = 0; i < allapp.size(); i++)
	{
		temp2 = x2;

		for (int j = 0; j < allapp[i].size(); j++)
		{
			allapp[i][j].setPosition(x1, temp2);
			temp2 += 30;
		}
	}

	for (int i = 0; i < allmain.size(); i++)
	{
		temp2 = x2;

		for (int j = 0; j < allmain[i].size(); j++)
		{
			allmain[i][j].setPosition(x1, temp2);
			temp2 += 30;
		}
	}

	for (int i = 0; i < alldes.size(); i++)
	{
		temp2 = x2;

		for (int j = 0; j < alldes[i].size(); j++)
		{
			alldes[i][j].setPosition(x1, temp2);
			temp2 += 30;
		}
	}

	for (int i = 0; i < alldri.size(); i++)
	{
		temp2 = x2;

		for (int j = 0; j < alldri[i].size(); j++)
		{
			alldri[i][j].setPosition(x1, temp2);
			temp2 += 30;
		}
	}

	for (int i = 0; i < privatenamesfromcustom.size(); i++)
	{
		temp2 = x2;

		for (int j = 0; j < privatenamesfromcustom[i].size(); j++)
		{
			privatenamesfromcustom[i][j].setPosition(x1, temp2);

			temp2 += 30.f;
		}
	}

	Sprite sprite1(texture1);
	sprite1.setPosition(0, 0);

	Sprite sprite2(texture2);
	sprite2.setPosition(0, 0);

	Sprite sprite3(texture3);
	sprite3.setPosition(0, 0);

	Sprite sprite4(texture4);
	sprite4.setPosition(0, 0);

	Sprite sprite5(texture5);
	sprite5.setPosition(0, 0);

	Sprite sprite6(texture6);
	sprite6.setPosition(0, 0);

	Sprite sprite7(texture7);
	sprite7.setPosition(0, 0);

	Sprite sprite8(texture8);
	sprite8.setPosition(0, 0);

	Sprite sprite9(texture9);
	sprite9.setPosition(0, 0);

	Sprite sprite10(texture10);
	sprite10.setPosition(0, 0);

	Sprite sprite11(texture11);
	sprite11.setPosition(0, 0);

	Sprite RightArrow(texture12);
	RightArrow.setPosition(500, 400);

	Sprite LeftArrow(texture13);
	LeftArrow.setPosition(50, 400);

	Sprite sprite14(texture14);
	sprite14.setPosition(0, 0);

	Text text1("- Press Escape to exit the book", font3, 18);
	text1.setFillColor(Color::White);
	text1.setPosition(175, 300);

	Text get("", font3, 25);
	get.setFillColor(Color::White);
	get.setOutlineThickness(5.f);
	get.setPosition(10, 20);

	Text Ing("Ingredients: ", font3, 20);
	Ing.setFillColor(Color::White);
	Ing.setOutlineThickness(3.f);
	Ing.setPosition(50, 50);

	Text Ins("Instructions: ", font3, 20);
	Ins.setFillColor(Color::White);
	Ins.setOutlineThickness(3.f);
	Ins.setPosition(50, 50);

	Text text2("- Press Enter to Enter your Own \n    Recipe", font3, 18);
	text2.setFillColor(Color::White);
	text2.setPosition(175, 330);

	Text text3("- Click here to access system recipes ", font3, 18);
	text3.setFillColor(Color::White);
	text3.setPosition(175, 390);

	Text text4("Username: ", font2, 20);
	text4.setFillColor(Color(202, 240, 248, 128));
	text4.setPosition(175, 403);

	Text text5("Password: ", font2, 20);
	text5.setFillColor(Color(202, 240, 248, 128));
	text5.setPosition(175, 453);

	Text text6("Create a new User: ", font2, 18);
	text6.setFillColor(Color(202, 240, 248, 128));
	text6.setPosition(320, 480);

	Text username("", font3, 20);
	username.setFillColor(Color::White);
	username.setPosition(175.f, 403.f);

	Text pass("", font2, 20);
	pass.setFillColor(Color::White);
	pass.setPosition(175.f, 453.f);

	Text DNE("Username or password incorrect enter again", font2, 20);
	DNE.setFillColor(Color::Red);
	DNE.setPosition(175.f, 505.f);

	Text app("- Appetizers ", font3, 30);
	app.setFillColor(Color(224, 159, 62));
	app.setPosition(10.f, 330.f);

	Text main("- Main-Course ", font3, 30);
	main.setFillColor(Color(224, 159, 62));
	main.setPosition(10.f, 390.f);

	Text Dess("- Desserts ", font3, 30);
	Dess.setFillColor(Color(224, 159, 62));
	Dess.setPosition(10.f, 450.f);

	Text Drinks("- Drinks ", font3, 30);
	Drinks.setFillColor(Color(224, 159, 62));
	Drinks.setPosition(10.f, 510.f);

	Text FL("- Feeling Lucky? ", font3, 30);
	FL.setFillColor(Color(224, 159, 62));
	FL.setPosition(10.f, 630.f);

	Text greeting("Welcome ", font3, 25);
	greeting.setFillColor(Color::White);
	greeting.setPosition(165.f, 250.f);

	RectangleShape Credintials1(Vector2f(250.f, 30.f));
	Credintials1.setFillColor(Color(0, 0, 0, 128));
	Credintials1.setPosition(170, 400.f);

	RectangleShape Cuisinename(Vector2f(325.f, 210.f));
	Cuisinename.setFillColor(Color(0, 0, 0, 128));
	Cuisinename.setPosition(150.f, 240.f);

	RectangleShape Cuisinenameshort(Vector2f(325.f, 30.f));
	Cuisinenameshort.setFillColor(Color(0, 0, 0, 128));
	Cuisinenameshort.setPosition(150.f, 240.f);

	RectangleShape RecipeFoodType(Vector2f(325.f, 150.f));
	RecipeFoodType.setFillColor(Color(0, 0, 0, 128));
	RecipeFoodType.setPosition(150.f, 280.f);

	RectangleShape RecipeFoodTypeshort(Vector2f(325.f, 30.f));
	RecipeFoodTypeshort.setFillColor(Color(0, 0, 0, 128));
	RecipeFoodTypeshort.setPosition(150.f, 280.f);

	RectangleShape RecipeNAME(Vector2f(325.f, 30.f));
	RecipeNAME.setFillColor(Color(0, 0, 0, 128));
	RecipeNAME.setPosition(150.f, 320.f);

	RectangleShape IngInput(Vector2f(325.f, 450.f));
	IngInput.setFillColor(Color(0, 0, 0, 128));
	IngInput.setPosition(150.f, 240.f);

	Text typeselection("Select From the following: ", font3, 22);
	typeselection.setFillColor(Color::White);
	typeselection.setPosition(152.f, 285.f);

	Text typedisplay("", font3, 20);
	typedisplay.setFillColor(Color::White);
	typedisplay.setPosition(155.f, 282.f);

	Text ap("Appetizer", font3, 20);
	ap.setFillColor(Color::White);
	ap.setPosition(155.f, 315.f);

	Text ma("Main-Course", font3, 20);
	ma.setFillColor(Color::White);
	ma.setPosition(155.f, 345.f);

	Text De("Dessert", font3, 20);
	De.setFillColor(Color::White);
	De.setPosition(155.f, 375.f);

	Text Dr("Drink", font3, 20);
	Dr.setFillColor(Color::White);
	Dr.setPosition(155.f, 405.f);

	RectangleShape RecipeIngredients(Vector2f(320.f, 150.f));
	RecipeIngredients.setFillColor(Color(0, 0, 0, 128));
	RecipeIngredients.setPosition(150.f, 360.f);

	RectangleShape RecipeInstructions(Vector2f(320.f, 150.f));
	RecipeInstructions.setFillColor(Color(0, 0, 0, 128));
	RecipeInstructions.setPosition(150.f, 530.f);

	Text In("Recipe Insertion: ", font3, 20);
	In.setPosition(150.f, 200.f);
	In.setOutlineThickness(3.f);

	Text forIngarrow("Click to enter the ingredients for the recipe", font3, 20);
	forIngarrow.setFillColor(Color(202, 240, 248, 128));
	forIngarrow.setPosition(135.f, 620.f);

	Text privacy("Do you want to share your recipe", font3, 20);
	privacy.setFillColor(Color::White);
	privacy.setPosition(152.f, 242.f);

	Text pub("Public", font3, 20);
	pub.setFillColor(Color::White);
	pub.setPosition(152.f, 272.f);

	Text priv("Private", font3, 20);
	priv.setFillColor(Color::White);
	priv.setPosition(152.f, 302.f);

	RectangleShape pri(Vector2f(325.f, 92.f));
	pri.setFillColor(Color(0, 0, 0, 128));
	pri.setPosition(150.f, 240.f);

	Text Cuisname("Cuisine-name: ", font3, 20);
	Cuisname.setFillColor(Color(202, 240, 248, 128));
	Cuisname.setPosition(155.f, 242.f);

	Text rname("Recipe-Name: ", font3, 20);
	rname.setFillColor(Color(202, 240, 248, 128));
	rname.setPosition(155.f, 322.f);

	Text Rname("", font3, 20);
	Rname.setFillColor(Color::White);
	Rname.setPosition(155.f, 322.f);

	Text  Cname("", font3, 20);
	Cname.setFillColor(Color::White);
	Cname.setPosition(155.f, 242.f);

	Text IG("Ingredients: ", font3, 20);
	IG.setFillColor(Color(202, 240, 248, 128));
	IG.setPosition(160.f, 250.f);

	float iginput = 250.f;

	Text IGinput("", font3, 12);
	IGinput.setFillColor(Color::White);
	IGinput.setPosition(160.f, 250.f);

	Text IGinputdup("", font3, 12);

	Text IS("Instructions: ", font3, 20);
	IS.setFillColor(Color(202, 240, 248, 128));
	IS.setPosition(160.f, 250.f);

	float isinput = 250.f;

	Text ISinput("", font3, 12);
	ISinput.setFillColor(Color::White);
	ISinput.setPosition(160.f, 250.f);

	Text ISinputdup("", font3, 12);

	RectangleShape Credintials2(Vector2f(250.f, 30.f));
	Credintials2.setFillColor(Color(0, 0, 0, 128));
	Credintials2.setPosition(170.f, 450.f);

	RectangleShape greet(Vector2f(500.f, 700.f));
	greet.setFillColor(Color(0, 0, 0, 128));
	greet.setPosition(50.f, 135.f);

	Text ty("Thank You :) ", font3, 45);
	ty.setFillColor(Color::White);
	ty.setPosition(185.f, 400.f);

	Text p("Your Private Recipes:", font3, 25);
	p.setFillColor(Color::Black);
	p.setPosition(175.f, 255.f);

	PageState currentpage = mainpage;

	bool isusernameactive = false;
	bool ispasswordactive = false;
	bool accessallowed = false;
	bool wronginput = false;
	bool newuser = false;

	LinkedList* usernames = new LinkedList();
	LinkedList* passwords = new LinkedList();

	readfile(usernames, passwords);

	while (window.isOpen())
	{
		while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed:
				if (ev.key.code == Keyboard::Escape)
					window.close();
				if (ev.key.code == Keyboard::Enter)
				{
					if (currentpage == mainpage)
					{
						currentpage = loginpage;
					}
					if (currentpage == greetingpage)
					{
						currentpage = recipeinput;
					}
					if (newuser)
					{
						writefile(username.getString().toAnsiString(), pass.getString().toAnsiString());

						newuser = false;

						currentpage = greetingpage;
					}
					else if (currentpage == loginpage)
					{
						string usernameinput = username.getString().toAnsiString();
						string passwordinput = pass.getString().toAnsiString();

						NodeforLL* usernamenode = usernames->head;
						NodeforLL* passnode = passwords->head;

						accessallowed = 0;

						while (usernamenode && passnode)
						{
							if (usernamenode->data == usernameinput && passnode->data == passwordinput)
							{
								accessallowed = 1;
								break;
							}

							usernamenode = usernamenode->next;

							passnode = passnode->next;

							usercount++;
						}
						if (accessallowed)
						{
							currentpage = greetingpage;
						}
						else
						{
							usercount = 0;

							if (flaguser && flagpass)
							{
								wronginput = 1;
								flaguser = 0;
								flagpass = 0;
								username.setString("");
								pass.setString("");
							}
						}
					}
					else if (isCuisinenameactive && typeselectionflag && isrecipenameactive)
					{
						donerecipe = true;
					}
					if (currentpage == recipeinput2)
					{
						IGinputdup.setString(IGinputdup.getString().toAnsiString() + IGinput.getString().toAnsiString() + "\n");

						IGinputdup.setPosition(160.f, 250.f);

						iginput += 15.f;

						IGinput.setPosition(160.f, iginput + temp3);

						temp3 += 1.f;

						customiginput.push_back(IGinput);

						IGinput.setString("");
					}
					else if (currentpage == recipeinput3)
					{
						ISinputdup.setString(ISinputdup.getString().toAnsiString() + ISinput.getString().toAnsiString() + "\n");

						ISinputdup.setPosition(160.f, 250.f);

						isinput += 15.f;

						ISinput.setPosition(160.f, isinput + temp4);

						temp4 += 1.f;

						customisinput.push_back(ISinput);

						ISinput.setString("");
					}
				}
				break;
			case Event::TextEntered:
				if (newuser)
				{
					if (isusernameactive)
					{
						if (ev.text.unicode == 8 && !username.getString().isEmpty())
						{
							username.setString(username.getString().substring(0, username.getString().getSize() - 1));
						}
						else if (ev.text.unicode >= 32 && ev.text.unicode < 127)
						{
							username.setString(username.getString() + static_cast<char>(ev.text.unicode));
						}
					}
					else if (ispasswordactive)
					{
						if (ev.text.unicode == 8 && !pass.getString().isEmpty())
						{
							pass.setString(pass.getString().substring(0, pass.getString().getSize() - 1));
						}
						else if (ev.text.unicode >= 32 && ev.text.unicode < 127)
						{
							pass.setString(pass.getString() + static_cast<char>(ev.text.unicode));
						}
					}
				}
				else if(currentpage == loginpage)
				{
					if (isusernameactive)
					{
						if (ev.text.unicode == 8 && !username.getString().isEmpty())
						{
							username.setString(username.getString().substring(0, username.getString().getSize() - 1));
						}
						else if (ev.text.unicode >= 32 && ev.text.unicode < 127)
						{
							username.setString(username.getString() + static_cast<char>(ev.text.unicode));
						}
					}
					else if (ispasswordactive)
					{
						if (ev.text.unicode == 8 && !pass.getString().isEmpty())
						{
							pass.setString(pass.getString().substring(0, pass.getString().getSize() - 1));
						}
						else if (ev.text.unicode >= 32 && ev.text.unicode < 127)
						{
							pass.setString(pass.getString() + static_cast<char>(ev.text.unicode));
						}
					}
				}
				else if (currentpage == recipeinput)
				{
					if (isrecipenameactive && !donerecipe)
					{
						if (ev.text.unicode == 8 && !Rname.getString().isEmpty())
						{
							Rname.setString(Rname.getString().substring(0, Rname.getString().getSize() - 1));
						}
						else if (ev.text.unicode >= 32 && ev.text.unicode < 127)
						{
							Rname.setString(Rname.getString() + static_cast<char>(ev.text.unicode));
						}
					}
				}
				else if (currentpage == recipeinput2)
				{
					if (isingactive)
					{
						if (ev.text.unicode == 8 && !IGinput.getString().isEmpty())
						{
							IGinput.setString(IGinput.getString().substring(0, IGinput.getString().getSize() - 1));
						}
						else if (ev.text.unicode >= 32 && ev.text.unicode < 127)
						{
							IGinput.setString(IGinput.getString() + static_cast<char>(ev.text.unicode));
						}
					}
				}
				else if (currentpage == recipeinput3)
				{
					if (isinsactive)
					{
						if (ev.text.unicode == 8 && !ISinput.getString().isEmpty())
						{
							ISinput.setString(ISinput.getString().substring(0, ISinput.getString().getSize() - 1));
						}
						else if (ev.text.unicode >= 32 && ev.text.unicode < 127)
						{
							ISinput.setString(ISinput.getString() + static_cast<char>(ev.text.unicode));
						}
					}
				}

				break;
			case Event::MouseButtonPressed:
				if (ev.mouseButton.button == Mouse::Left)
				{
					if (currentpage == loginpage)
					{
						if (text6.getGlobalBounds().contains(int(ev.mouseButton.x), int(ev.mouseButton.y)))
						{
							newuser = true;
							currentcount += 1;
						}
						else if (Credintials1.getGlobalBounds().contains(int(ev.mouseButton.x), int(ev.mouseButton.y)))
						{
							isusernameactive = true;
							flaguser = true;
							ispasswordactive = false;
						}
						else if (Credintials2.getGlobalBounds().contains(int(ev.mouseButton.x), int(ev.mouseButton.y)))
						{
							isusernameactive = false;
							ispasswordactive = true;
							flagpass = true;
						}
						else
						{
							isusernameactive = false;
							ispasswordactive = false;
						}
					}
					if (currentpage == greetingpage)
					{
						if (text3.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = askpage;
						}
					}
					if (currentpage == askpage)
					{
						if (app.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							isappetizeractive = true;

							currentpage = appetizerpage;
						}
						else if (main.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							ismaincourseactive = true;

							currentpage = maincoursepage;
						}
						else if (Dess.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							isdessertactive = true;

							currentpage = dessertpage;
						}
						else if (Drinks.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							isdrinkactive = true;

							currentpage = drinkspage;
						}
						else if (priv.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage25;
						}
						else if (FL.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = flpage;
						}
						
					}
					else if (currentpage == appetizerpage)
					{
						if (RightArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage;
						}
						else if (LeftArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = askpage;
						}
					}
					else if (currentpage == maincoursepage)
					{
						if (RightArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage7;
						}
						else if (LeftArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = askpage;
						}
					}
					else if (currentpage == dessertpage)
					{
						if (RightArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage13;
						}
						else if (LeftArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = askpage;
						}
					}
					else if (currentpage == drinkspage)
					{
						if (RightArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage19;
						}
						else if (LeftArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = askpage;
						}
					}
					else if (currentpage == recipepage)
					{
						if (RightArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage2;
						}
						else if (LeftArrow.getGlobalBounds().contains((ev.mouseButton.x), ev.mouseButton.y))
						{
							currentpage = askpage;
						}
						else
						{
							for (int i = 0; i < allapp[0].size(); i++)
							{
								if (allapp[0][i].getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
								{
									get.setString(allapp[0][i].getString().toAnsiString());

									string Input = allapp[0][i].getString().toAnsiString();

									currentpage = recipeprintingpage;

									NodeforHash* p = input->SearchSpecific(Input);

									float p8 = 120.f;

									recipeprintingIng.erase(recipeprintingIng.begin(), recipeprintingIng.end());
									recipeprintingIns.erase(recipeprintingIns.begin(), recipeprintingIns.end());

									NodeforLL* n = p->Ingredients->head;
									NodeforLL* na = p->Instructions->head;

									while (n != NULL)
									{
										Text t(n->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIng.push_back(t);
										n = n->next;
									}

									p8 = 120.f;

									while (na != NULL)
									{
										Text t(na->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIns.push_back(t);
										na = na->next;
									}

								}
							}
						}
					}
					else if (currentpage == recipepage2)
					{
						if (LeftArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage;
						}
						else if (RightArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage3;
						}
						else
						{
							for (int i = 0; i < allapp[1].size(); i++)
							{
								if (allapp[1][i].getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
								{
									get.setString(allapp[1][i].getString().toAnsiString());

									string Input = allapp[1][i].getString().toAnsiString();

									currentpage = recipeprintingpage;

									NodeforHash* p = input->SearchSpecific(Input);

									float p8 = 120.f;

									recipeprintingIng.erase(recipeprintingIng.begin(), recipeprintingIng.end());
									recipeprintingIns.erase(recipeprintingIns.begin(), recipeprintingIns.end());

									NodeforLL* n = p->Ingredients->head;
									NodeforLL* na = p->Instructions->head;

									while (n != NULL)
									{
										Text t(n->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIng.push_back(t);
										n = n->next;
									}

									p8 = 120.f;

									while (na != NULL)
									{
										Text t(na->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIns.push_back(t);
										na = na->next;
									}
								}
							}
						}
					}
					else if (currentpage == recipepage3)
					{
					if (LeftArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
					{
						currentpage = recipepage2;
					}
					else if (RightArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
					{
						currentpage = recipepage4;
					}
					else
					{
						for (int i = 0; i < allapp[2].size(); i++)
						{
							if (allapp[2][i].getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
							{
								get.setString(allapp[2][i].getString().toAnsiString());

								string Input = allapp[2][i].getString().toAnsiString();

								currentpage = recipeprintingpage;

								NodeforHash* p = input->SearchSpecific(Input);

								float p8 = 120.f;

								recipeprintingIng.erase(recipeprintingIng.begin(), recipeprintingIng.end());
								recipeprintingIns.erase(recipeprintingIns.begin(), recipeprintingIns.end());

								NodeforLL* n = p->Ingredients->head;
								NodeforLL* na = p->Instructions->head;

								while (n != NULL)
								{
									Text t(n->data, font3, 15);
									t.setPosition(80.f, p8);
									t.setOutlineThickness(3.f);
									p8 += 30.f;
									recipeprintingIng.push_back(t);
									n = n->next;
								}

								p8 = 120.f;

								while (na != NULL)
								{
									Text t(na->data, font3, 15);
									t.setPosition(80.f, p8);
									t.setOutlineThickness(3.f);
									p8 += 30.f;
									recipeprintingIns.push_back(t);
									na = na->next;
								}
							}
						}
					}
					}
					else if (currentpage == recipepage4)
					{
						if (LeftArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage3;
						}
						else if (RightArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage5;
						}
						else
						{
							for (int i = 0; i < allapp[3].size(); i++)
							{
								if (allapp[3][i].getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
								{
									get.setString(allapp[3][i].getString().toAnsiString());
									
									string Input = allapp[3][i].getString().toAnsiString();

									currentpage = recipeprintingpage;

									NodeforHash* p = input->SearchSpecific(Input);

									float p8 = 120.f;

									recipeprintingIng.erase(recipeprintingIng.begin(), recipeprintingIng.end());
									recipeprintingIns.erase(recipeprintingIns.begin(), recipeprintingIns.end());

									NodeforLL* n = p->Ingredients->head;
									NodeforLL* na = p->Instructions->head;

									while (n != NULL)
									{
										Text t(n->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIng.push_back(t);
										n = n->next;
									}

									p8 = 120.f;

									while (na != NULL)
									{
										Text t(na->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIns.push_back(t);
										na = na->next;
									}
								}
							}
						}
					}
					else if (currentpage == recipepage5)
					{
						if (LeftArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage4;
						}
						else if (RightArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage6;
						}
						else
						{
							for (int i = 0; i < allapp[4].size(); i++)
							{
								if (allapp[4][i].getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
								{
									get.setString(allapp[4][i].getString().toAnsiString());

									string Input = allapp[4][i].getString().toAnsiString();

									currentpage = recipeprintingpage;

									NodeforHash* p = input->SearchSpecific(Input);

									float p8 = 120.f;

									recipeprintingIng.erase(recipeprintingIng.begin(), recipeprintingIng.end());
									recipeprintingIns.erase(recipeprintingIns.begin(), recipeprintingIns.end());

									NodeforLL* n = p->Ingredients->head;
									NodeforLL* na = p->Instructions->head;

									while (n != NULL)
									{
										Text t(n->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIng.push_back(t);
										n = n->next;
									}

									p8 = 120.f;

									while (na != NULL)
									{
										Text t(na->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIns.push_back(t);
										na = na->next;
									}
								}
							}
						}
					}
					else if (currentpage == recipepage6)
					{
						if (LeftArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage5;
						}
						else if (RightArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = askpage;
						}
						else
						{
							for (int i = 0; i < allapp[5].size(); i++)
							{
								if (allapp[5][i].getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
								{
									get.setString(allapp[5][i].getString().toAnsiString());

									string Input = allapp[5][i].getString().toAnsiString();

									currentpage = recipeprintingpage;

									NodeforHash* p = input->SearchSpecific(Input);

									float p8 = 120.f;

									recipeprintingIng.erase(recipeprintingIng.begin(), recipeprintingIng.end());
									recipeprintingIns.erase(recipeprintingIns.begin(), recipeprintingIns.end());

									NodeforLL* n = p->Ingredients->head;
									NodeforLL* na = p->Instructions->head;

									while (n != NULL)
									{
										Text t(n->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIng.push_back(t);
										n = n->next;
									}

									p8 = 120.f;

									while (na != NULL)
									{
										Text t(na->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIns.push_back(t);
										na = na->next;
									}
								}
							}
						}
					}
					else if (currentpage == recipepage7)
					{
						if (RightArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage8;
						}
						else if (LeftArrow.getGlobalBounds().contains((ev.mouseButton.x), ev.mouseButton.y))
						{
							currentpage = askpage;
						}
						else
						{
							for (int i = 0; i < allmain[0].size(); i++)
							{
								if (allmain[0][i].getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
								{
									get.setString(allmain[0][i].getString().toAnsiString());

									string Input = allmain[0][i].getString().toAnsiString();

									currentpage = recipeprintingpage;

									NodeforHash* p = input->SearchSpecific(Input);

									float p8 = 120.f;

									recipeprintingIng.erase(recipeprintingIng.begin(), recipeprintingIng.end());
									recipeprintingIns.erase(recipeprintingIns.begin(), recipeprintingIns.end());

									NodeforLL* n = p->Ingredients->head;
									NodeforLL* na = p->Instructions->head;

									while (n != NULL)
									{
										Text t(n->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIng.push_back(t);
										n = n->next;
									}

									p8 = 120.f;

									while (na != NULL)
									{
										Text t(na->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIns.push_back(t);
										na = na->next;
									}

								}
							}
						}
					}
					else if (currentpage == recipepage8)
					{
						if (LeftArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage7;
						}
						else if (RightArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage9;
						}
						else
						{
							for (int i = 0; i < allmain[1].size(); i++)
							{
								if (allmain[1][i].getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
								{
									get.setString(allmain[1][i].getString().toAnsiString());

									string Input = allmain[1][i].getString().toAnsiString();

									currentpage = recipeprintingpage;

									NodeforHash* p = input->SearchSpecific(Input);

									float p8 = 120.f;

									recipeprintingIng.erase(recipeprintingIng.begin(), recipeprintingIng.end());
									recipeprintingIns.erase(recipeprintingIns.begin(), recipeprintingIns.end());

									NodeforLL* n = p->Ingredients->head;
									NodeforLL* na = p->Instructions->head;

									while (n != NULL)
									{
										Text t(n->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIng.push_back(t);
										n = n->next;
									}

									p8 = 120.f;

									while (na != NULL)
									{
										Text t(na->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIns.push_back(t);
										na = na->next;
									}
								}
							}
						}
					}
					else if (currentpage == recipepage9)
					{
						if (LeftArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage8;
						}
						else if (RightArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage10;
						}
						else
						{
							for (int i = 0; i < allmain[2].size(); i++)
							{
								if (allmain[2][i].getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
								{
									get.setString(allmain[2][i].getString().toAnsiString());

									string Input = allmain[2][i].getString().toAnsiString();

									currentpage = recipeprintingpage;

									NodeforHash* p = input->SearchSpecific(Input);

									float p8 = 120.f;

									recipeprintingIng.erase(recipeprintingIng.begin(), recipeprintingIng.end());
									recipeprintingIns.erase(recipeprintingIns.begin(), recipeprintingIns.end());

									NodeforLL* n = p->Ingredients->head;
									NodeforLL* na = p->Instructions->head;

									while (n != NULL)
									{
										Text t(n->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIng.push_back(t);
										n = n->next;
									}

									p8 = 120.f;

									while (na != NULL)
									{
										Text t(na->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIns.push_back(t);
										na = na->next;
									}
								}
							}
						}
					}
					else if (currentpage == recipepage10)
					{
						if (LeftArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage9;
						}
						else if (RightArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage11;
						}
						else
						{
							for (int i = 0; i < allmain[3].size(); i++)
							{
								if (allmain[3][i].getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
								{
									get.setString(allmain[3][i].getString().toAnsiString());

									string Input = allmain[3][i].getString().toAnsiString();

									currentpage = recipeprintingpage;

									NodeforHash* p = input->SearchSpecific(Input);

									float p8 = 120.f;

									recipeprintingIng.erase(recipeprintingIng.begin(), recipeprintingIng.end());
									recipeprintingIns.erase(recipeprintingIns.begin(), recipeprintingIns.end());

									NodeforLL* n = p->Ingredients->head;
									NodeforLL* na = p->Instructions->head;

									while (n != NULL)
									{
										Text t(n->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIng.push_back(t);
										n = n->next;
									}

									p8 = 120.f;

									while (na != NULL)
									{
										Text t(na->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIns.push_back(t);
										na = na->next;
									}
								}
							}
						}
					}
					else if (currentpage == recipepage11)
					{
						if (LeftArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage10;
						}
						else if (RightArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage12;
						}
						else
						{
							for (int i = 0; i < allmain[4].size(); i++)
							{
								if (allmain[4][i].getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
								{
									get.setString(allmain[4][i].getString().toAnsiString());

									string Input = allmain[4][i].getString().toAnsiString();

									currentpage = recipeprintingpage;

									NodeforHash* p = input->SearchSpecific(Input);

									float p8 = 120.f;

									recipeprintingIng.erase(recipeprintingIng.begin(), recipeprintingIng.end());
									recipeprintingIns.erase(recipeprintingIns.begin(), recipeprintingIns.end());

									NodeforLL* n = p->Ingredients->head;
									NodeforLL* na = p->Instructions->head;

									while (n != NULL)
									{
										Text t(n->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIng.push_back(t);
										n = n->next;
									}

									p8 = 120.f;

									while (na != NULL)
									{
										Text t(na->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIns.push_back(t);
										na = na->next;
									}
								}
							}
						}
					}
					else if (currentpage == recipepage12)
					{
						if (LeftArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage11;
						}
						else if (RightArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = askpage;
						}
						else
						{
							for (int i = 0; i < allmain[5].size(); i++)
							{
								if (allmain[5][i].getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
								{
									get.setString(allmain[5][i].getString().toAnsiString());

									string Input = allmain[5][i].getString().toAnsiString();

									currentpage = recipeprintingpage;

									NodeforHash* p = input->SearchSpecific(Input);

									float p8 = 120.f;

									recipeprintingIng.erase(recipeprintingIng.begin(), recipeprintingIng.end());
									recipeprintingIns.erase(recipeprintingIns.begin(), recipeprintingIns.end());

									NodeforLL* n = p->Ingredients->head;
									NodeforLL* na = p->Instructions->head;

									while (n != NULL)
									{
										Text t(n->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIng.push_back(t);
										n = n->next;
									}

									p8 = 120.f;

									while (na != NULL)
									{
										Text t(na->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIns.push_back(t);
										na = na->next;
									}
								}
							}
						}
					}
					else if (currentpage == recipepage13)
					{
						if (RightArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage14;
						}
						else if (LeftArrow.getGlobalBounds().contains((ev.mouseButton.x), ev.mouseButton.y))
						{
							currentpage = askpage;
						}
						else
						{
							for (int i = 0; i < alldes[0].size(); i++)
							{
								if (alldes[0][i].getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
								{
									get.setString(alldes[0][i].getString().toAnsiString());

									string Input = alldes[0][i].getString().toAnsiString();

									currentpage = recipeprintingpage;

									NodeforHash* p = input->SearchSpecific(Input);

									float p8 = 120.f;

									recipeprintingIng.erase(recipeprintingIng.begin(), recipeprintingIng.end());
									recipeprintingIns.erase(recipeprintingIns.begin(), recipeprintingIns.end());

									NodeforLL* n = p->Ingredients->head;
									NodeforLL* na = p->Instructions->head;

									while (n != NULL)
									{
										Text t(n->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIng.push_back(t);
										n = n->next;
									}

									p8 = 120.f;

									while (na != NULL)
									{
										Text t(na->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIns.push_back(t);
										na = na->next;
									}

								}
							}
						}
					}
					else if (currentpage == recipepage14)
					{
						if (LeftArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage13;
						}
						else if (RightArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage15;
						}
						else
						{
							for (int i = 0; i < alldes[1].size(); i++)
							{
								if (alldes[1][i].getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
								{
									get.setString(alldes[1][i].getString().toAnsiString());

									string Input = alldes[1][i].getString().toAnsiString();

									currentpage = recipeprintingpage;

									NodeforHash* p = input->SearchSpecific(Input);

									float p8 = 120.f;

									recipeprintingIng.erase(recipeprintingIng.begin(), recipeprintingIng.end());
									recipeprintingIns.erase(recipeprintingIns.begin(), recipeprintingIns.end());

									NodeforLL* n = p->Ingredients->head;
									NodeforLL* na = p->Instructions->head;

									while (n != NULL)
									{
										Text t(n->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIng.push_back(t);
										n = n->next;
									}

									p8 = 120.f;

									while (na != NULL)
									{
										Text t(na->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIns.push_back(t);
										na = na->next;
									}
								}
							}
						}
					}
					else if (currentpage == recipepage15)
					{
						if (LeftArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage14;
						}
						else if (RightArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage16;
						}
						else
						{
							for (int i = 0; i < alldes[2].size(); i++)
							{
								if (alldes[2][i].getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
								{
									get.setString(alldes[2][i].getString().toAnsiString());

									string Input = alldes[2][i].getString().toAnsiString();

									currentpage = recipeprintingpage;

									NodeforHash* p = input->SearchSpecific(Input);

									float p8 = 120.f;

									recipeprintingIng.erase(recipeprintingIng.begin(), recipeprintingIng.end());
									recipeprintingIns.erase(recipeprintingIns.begin(), recipeprintingIns.end());

									NodeforLL* n = p->Ingredients->head;
									NodeforLL* na = p->Instructions->head;

									while (n != NULL)
									{
										Text t(n->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIng.push_back(t);
										n = n->next;
									}

									p8 = 120.f;

									while (na != NULL)
									{
										Text t(na->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIns.push_back(t);
										na = na->next;
									}
								}
							}
						}
					}
					else if (currentpage == recipepage16)
					{
						if (LeftArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage15;
						}
						else if (RightArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage17;
						}
						else
						{
							for (int i = 0; i < alldes[3].size(); i++)
							{
								if (alldes[3][i].getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
								{
									get.setString(alldes[3][i].getString().toAnsiString());

									string Input = alldes[3][i].getString().toAnsiString();

									currentpage = recipeprintingpage;

									NodeforHash* p = input->SearchSpecific(Input);

									float p8 = 120.f;

									recipeprintingIng.erase(recipeprintingIng.begin(), recipeprintingIng.end());
									recipeprintingIns.erase(recipeprintingIns.begin(), recipeprintingIns.end());

									NodeforLL* n = p->Ingredients->head;
									NodeforLL* na = p->Instructions->head;

									while (n != NULL)
									{
										Text t(n->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIng.push_back(t);
										n = n->next;
									}

									p8 = 120.f;

									while (na != NULL)
									{
										Text t(na->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIns.push_back(t);
										na = na->next;
									}
								}
							}
						}
					}
					else if (currentpage == recipepage17)
					{
						if (LeftArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage16;
						}
						else if (RightArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage18;
						}
						else
						{
							for (int i = 0; i < alldes[4].size(); i++)
							{
								if (alldes[4][i].getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
								{
									get.setString(alldes[4][i].getString().toAnsiString());

									string Input = alldes[4][i].getString().toAnsiString();

									currentpage = recipeprintingpage;

									NodeforHash* p = input->SearchSpecific(Input);

									float p8 = 120.f;

									recipeprintingIng.erase(recipeprintingIng.begin(), recipeprintingIng.end());
									recipeprintingIns.erase(recipeprintingIns.begin(), recipeprintingIns.end());

									NodeforLL* n = p->Ingredients->head;
									NodeforLL* na = p->Instructions->head;

									while (n != NULL)
									{
										Text t(n->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIng.push_back(t);
										n = n->next;
									}

									p8 = 120.f;

									while (na != NULL)
									{
										Text t(na->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIns.push_back(t);
										na = na->next;
									}
								}
							}
						}
					}
					else if (currentpage == recipepage18)
					{
						if (LeftArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage17;
						}
						else if (RightArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = askpage;
						}
						else
						{
							for (int i = 0; i < alldes[5].size(); i++)
							{
								if (alldes[5][i].getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
								{
									get.setString(alldes[5][i].getString().toAnsiString());

									string Input = alldes[5][i].getString().toAnsiString();

									currentpage = recipeprintingpage;

									NodeforHash* p = input->SearchSpecific(Input);

									float p8 = 120.f;

									recipeprintingIng.erase(recipeprintingIng.begin(), recipeprintingIng.end());
									recipeprintingIns.erase(recipeprintingIns.begin(), recipeprintingIns.end());

									NodeforLL* n = p->Ingredients->head;
									NodeforLL* na = p->Instructions->head;

									while (n != NULL)
									{
										Text t(n->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIng.push_back(t);
										n = n->next;
									}

									p8 = 120.f;

									while (na != NULL)
									{
										Text t(na->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIns.push_back(t);
										na = na->next;
									}
								}
							}
						}
					}
					else if (currentpage == recipepage19)
					{
						if (RightArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage20;
						}
						else if (LeftArrow.getGlobalBounds().contains((ev.mouseButton.x), ev.mouseButton.y))
						{
							currentpage = askpage;
						}
						else
						{
							for (int i = 0; i < alldes[0].size(); i++)
							{
								if (alldri[0][i].getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
								{
									get.setString(alldri[0][i].getString().toAnsiString());

									string Input = alldri[0][i].getString().toAnsiString();

									currentpage = recipeprintingpage;

									NodeforHash* p = input->SearchSpecific(Input);

									float p8 = 120.f;

									recipeprintingIng.erase(recipeprintingIng.begin(), recipeprintingIng.end());
									recipeprintingIns.erase(recipeprintingIns.begin(), recipeprintingIns.end());

									NodeforLL* n = p->Ingredients->head;
									NodeforLL* na = p->Instructions->head;

									while (n != NULL)
									{
										Text t(n->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIng.push_back(t);
										n = n->next;
									}

									p8 = 120.f;

									while (na != NULL)
									{
										Text t(na->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIns.push_back(t);
										na = na->next;
									}

								}
							}
						}
					}
					else if (currentpage == recipepage20)
					{
						if (LeftArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage19;
						}
						else if (RightArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage21;
						}
						else
						{
							for (int i = 0; i < alldri[1].size(); i++)
							{
								if (alldri[1][i].getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
								{
									get.setString(alldri[1][i].getString().toAnsiString());

									string Input = alldri[1][i].getString().toAnsiString();

									currentpage = recipeprintingpage;

									NodeforHash* p = input->SearchSpecific(Input);

									float p8 = 120.f;

									recipeprintingIng.erase(recipeprintingIng.begin(), recipeprintingIng.end());
									recipeprintingIns.erase(recipeprintingIns.begin(), recipeprintingIns.end());

									NodeforLL* n = p->Ingredients->head;
									NodeforLL* na = p->Instructions->head;

									while (n != NULL)
									{
										Text t(n->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIng.push_back(t);
										n = n->next;
									}

									p8 = 120.f;

									while (na != NULL)
									{
										Text t(na->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIns.push_back(t);
										na = na->next;
									}
								}
							}
						}
					}
					else if (currentpage == recipepage21)
					{
						if (LeftArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage20;
						}
						else if (RightArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage22;
						}
						else
						{
							for (int i = 0; i < alldri[2].size(); i++)
							{
								if (alldri[2][i].getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
								{
									get.setString(alldri[2][i].getString().toAnsiString());

									string Input = alldri[2][i].getString().toAnsiString();

									currentpage = recipeprintingpage;

									NodeforHash* p = input->SearchSpecific(Input);

									float p8 = 120.f;

									recipeprintingIng.erase(recipeprintingIng.begin(), recipeprintingIng.end());
									recipeprintingIns.erase(recipeprintingIns.begin(), recipeprintingIns.end());

									NodeforLL* n = p->Ingredients->head;
									NodeforLL* na = p->Instructions->head;

									while (n != NULL)
									{
										Text t(n->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIng.push_back(t);
										n = n->next;
									}

									p8 = 120.f;

									while (na != NULL)
									{
										Text t(na->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIns.push_back(t);
										na = na->next;
									}
								}
							}
						}
					}
					else if (currentpage == recipepage22)
					{
						if (LeftArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage21;
						}
						else if (RightArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage23;
						}
						else
						{
							for (int i = 0; i < alldri[3].size(); i++)
							{
								if (alldri[3][i].getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
								{
									get.setString(alldri[3][i].getString().toAnsiString());

									string Input = alldri[3][i].getString().toAnsiString();

									currentpage = recipeprintingpage;

									NodeforHash* p = input->SearchSpecific(Input);

									float p8 = 120.f;

									recipeprintingIng.erase(recipeprintingIng.begin(), recipeprintingIng.end());
									recipeprintingIns.erase(recipeprintingIns.begin(), recipeprintingIns.end());

									NodeforLL* n = p->Ingredients->head;
									NodeforLL* na = p->Instructions->head;

									while (n != NULL)
									{
										Text t(n->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIng.push_back(t);
										n = n->next;
									}

									p8 = 120.f;

									while (na != NULL)
									{
										Text t(na->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIns.push_back(t);
										na = na->next;
									}
								}
							}
						}
					}
					else if (currentpage == recipepage23)
					{
						if (LeftArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage22;
						}
						else if (RightArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage24;
						}
						else
						{
							for (int i = 0; i < alldri[4].size(); i++)
							{
								if (alldri[4][i].getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
								{
									get.setString(alldri[4][i].getString().toAnsiString());

									string Input = alldri[4][i].getString().toAnsiString();

									currentpage = recipeprintingpage;

									NodeforHash* p = input->SearchSpecific(Input);

									float p8 = 120.f;

									recipeprintingIng.erase(recipeprintingIng.begin(), recipeprintingIng.end());
									recipeprintingIns.erase(recipeprintingIns.begin(), recipeprintingIns.end());

									NodeforLL* n = p->Ingredients->head;
									NodeforLL* na = p->Instructions->head;

									while (n != NULL)
									{
										Text t(n->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIng.push_back(t);
										n = n->next;
									}

									p8 = 120.f;

									while (na != NULL)
									{
										Text t(na->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIns.push_back(t);
										na = na->next;
									}
								}
							}
						}
					}
					else if (currentpage == recipepage24)
					{
						if (LeftArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipepage23;
						}
						else
						{
							for (int i = 0; i < alldri[5].size(); i++)
							{
								if (alldri[5][i].getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
								{
									get.setString(alldri[5][i].getString().toAnsiString());

									string Input = alldri[5][i].getString().toAnsiString();

									currentpage = recipeprintingpage;

									NodeforHash* p = input->SearchSpecific(Input);

									float p8 = 120.f;

									recipeprintingIng.erase(recipeprintingIng.begin(), recipeprintingIng.end());
									recipeprintingIns.erase(recipeprintingIns.begin(), recipeprintingIns.end());

									NodeforLL* n = p->Ingredients->head;
									NodeforLL* na = p->Instructions->head;

									while (n != NULL)
									{
										Text t(n->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIng.push_back(t);
										n = n->next;
									}

									p8 = 120.f;

									while (na != NULL)
									{
										Text t(na->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIns.push_back(t);
										na = na->next;
									}
								}
							}
						}
					}
					else if (currentpage == recipepage25)
					{
						if (LeftArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = askpage;
						}
						else
						{
							for (int i = 0; i < privatenamesfromcustom[usercount].size(); i++)
							{
								if (privatenamesfromcustom[usercount][i].getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
								{
									get.setString(privatenamesfromcustom[usercount][i].getString().toAnsiString());

									string Input = privatenamesfromcustom[usercount][i].getString().toAnsiString();

									currentpage = recipeprintingpage;

									NodeforHash* p = priva[usercount]->SearchSpecific(Input);

									float p8 = 120.f;

									recipeprintingIng.erase(recipeprintingIng.begin(), recipeprintingIng.end());
									recipeprintingIns.erase(recipeprintingIns.begin(), recipeprintingIns.end());

									NodeforLL* n = p->Ingredients->head;
									NodeforLL* na = p->Instructions->head;

									while (n != NULL)
									{
										Text t(n->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIng.push_back(t);
										n = n->next;
									}

									p8 = 120.f;

									while (na != NULL)
									{
										Text t(na->data, font3, 15);
										t.setPosition(80.f, p8);
										t.setOutlineThickness(3.f);
										p8 += 30.f;
										recipeprintingIns.push_back(t);
										na = na->next;
									}
								}
							}
						}
					}
					else if (currentpage == recipeprintingpage)
					{
						if (LeftArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = askpage;
						}
						else if (RightArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipeprintingpage2;
						}
					}
					else if (currentpage == recipeprintingpage2)
					{
						if (LeftArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipeprintingpage;
						}
					}
					else if (currentpage == recipeinput)
					{
						if (!isCuisinenameactive)
						{
							for (int i = 0; i < textvector.size(); i++)
							{
								if (textvector[i].getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
								{
									isCuisinenameactive = true;

									Cname.setString(textvector[i].getString().toAnsiString());
								}
							}
						}
						else if (isCuisinenameactive)
						{
							if (Cname.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
							{
								isCuisinenameactive = false;
								typeselectionflag = false;
								isrecipenameactive = false;
							}
						}
						if (!typeselectionflag && isCuisinenameactive)
						{
							if (ap.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
							{
								typeselectionflag = true;
								typedisplay.setString("Appetizer");
							}
							else if (ma.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
							{
								typeselectionflag = true;
								typedisplay.setString("Main-Course");
							}
							else if (Dr.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
							{
								typeselectionflag = true;
								typedisplay.setString("Drink");
							}
							else if (De.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
							{
								typeselectionflag = true;
								typedisplay.setString("Dessert");
							}
						}
						else if (typeselectionflag)
						{
							if (typedisplay.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
							{
								typeselectionflag = false;
								isrecipenameactive = false;
							}
							else if (isCuisinenameactive)
							{
								if (rname.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
								{
									isrecipenameactive = true;
								}
							}
						}
						if (donerecipe)
						{
							if (RightArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
							{
								currentpage = recipeinput2;
							}
						}
						
					}
					else if (currentpage == recipeinput2)
					{
						if (IG.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							isingactive = true;
						}
						if (RightArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y) && isingactive)
						{
							currentpage = recipeinput3;
						}
					}
					else if (currentpage == recipeinput3)
					{
						if (IS.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							isinsactive = true;
						}
						if (RightArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y) && isinsactive)
						{
							currentpage = recipesubmitted;
						}


					}
					else if (currentpage == recipesubmitted)
					{
						if (pub.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							wantpublic = true;
						}

						if (priv.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							wantprivate = true;
						}
					}
					else if (currentpage == thankyou)
					{
						if (LeftArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							window.close();
						}
					}
					else if (currentpage == flpage)
					{
						if (app.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							int l = rand() % allapp.size();

							int m = rand() % allapp[l].size();

							currentpage = flrecipenamepage;

							NodeforHash* p = input->SearchSpecific(allapp[l][m].getString().toAnsiString());

							flrecipename = allapp[l][m].getString().toAnsiString();

							float p8 = 120.f;

							recipeprintingIng.erase(recipeprintingIng.begin(), recipeprintingIng.end());
							recipeprintingIns.erase(recipeprintingIns.begin(), recipeprintingIns.end());

							NodeforLL* n = p->Ingredients->head;
							NodeforLL* na = p->Instructions->head;

							while (n != NULL)
							{
								Text t(n->data, font3, 15);
								t.setPosition(80.f, p8);
								t.setOutlineThickness(3.f);
								p8 += 30.f;
								recipeprintingIng.push_back(t);
								n = n->next;
							}

							p8 = 120.f;

							while (na != NULL)
							{
								Text t(na->data, font3, 15);
								t.setPosition(80.f, p8);
								t.setOutlineThickness(3.f);
								p8 += 30.f;
								recipeprintingIns.push_back(t);
								na = na->next;
							}
						}
						else if (main.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							int l = rand() % allmain.size();

							int m = rand() % allmain[l].size();

							currentpage = flrecipenamepage;

							NodeforHash* p = input->SearchSpecific(allmain[l][m].getString().toAnsiString());

							flrecipename = allmain[l][m].getString().toAnsiString();

							float p8 = 120.f;

							recipeprintingIng.erase(recipeprintingIng.begin(), recipeprintingIng.end());
							recipeprintingIns.erase(recipeprintingIns.begin(), recipeprintingIns.end());

							NodeforLL* n = p->Ingredients->head;
							NodeforLL* na = p->Instructions->head;

							while (n != NULL)
							{
								Text t(n->data, font3, 15);
								t.setPosition(80.f, p8);
								t.setOutlineThickness(3.f);
								p8 += 30.f;
								recipeprintingIng.push_back(t);
								n = n->next;
							}

							p8 = 120.f;

							while (na != NULL)
							{
								Text t(na->data, font3, 15);
								t.setPosition(80.f, p8);
								t.setOutlineThickness(3.f);
								p8 += 30.f;
								recipeprintingIns.push_back(t);
								na = na->next;
							}
						}
						else if (Dess.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							int l = rand() % alldes.size();

							int m = rand() % alldes[l].size();

							currentpage = flrecipenamepage;

							NodeforHash* p = input->SearchSpecific(alldes[l][m].getString().toAnsiString());

							flrecipename = alldes[l][m].getString().toAnsiString();

							float p8 = 120.f;

							recipeprintingIng.erase(recipeprintingIng.begin(), recipeprintingIng.end());
							recipeprintingIns.erase(recipeprintingIns.begin(), recipeprintingIns.end());

							NodeforLL* n = p->Ingredients->head;
							NodeforLL* na = p->Instructions->head;

							while (n != NULL)
							{
								Text t(n->data, font3, 15);
								t.setPosition(80.f, p8);
								t.setOutlineThickness(3.f);
								p8 += 30.f;
								recipeprintingIng.push_back(t);
								n = n->next;
							}

							p8 = 120.f;

							while (na != NULL)
							{
								Text t(na->data, font3, 15);
								t.setPosition(80.f, p8);
								t.setOutlineThickness(3.f);
								p8 += 30.f;
								recipeprintingIns.push_back(t);
								na = na->next;
							}
						}
						else if (Drinks.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							int l = rand() % alldri.size();

							int m = rand() % alldri[l].size();

							currentpage = flrecipenamepage;

							flrecipename = alldri[l][m].getString().toAnsiString();

							NodeforHash* p = input->SearchSpecific(alldri[l][m].getString().toAnsiString());

							float p8 = 120.f;

							recipeprintingIng.erase(recipeprintingIng.begin(), recipeprintingIng.end());
							recipeprintingIns.erase(recipeprintingIns.begin(), recipeprintingIns.end());

							NodeforLL* n = p->Ingredients->head;
							NodeforLL* na = p->Instructions->head;

							while (n != NULL)
							{
								Text t(n->data, font3, 15);
								t.setPosition(80.f, p8);
								t.setOutlineThickness(3.f);
								p8 += 30.f;
								recipeprintingIng.push_back(t);
								n = n->next;
							}

							p8 = 120.f;

							while (na != NULL)
							{
								Text t(na->data, font3, 15);
								t.setPosition(80.f, p8);
								t.setOutlineThickness(3.f);
								p8 += 30.f;
								recipeprintingIns.push_back(t);
								na = na->next;
							}
						}
					}
					else if (currentpage == flrecipenamepage)
					{
						if (LeftArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = flpage;
						}
						else if (RightArrow.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y))
						{
							currentpage = recipeprintingpage;
						}
					}
				}
				break;
			}
		}

		window.clear(Color(02, 30, 47));

		if (currentpage == mainpage)
		{
			window.draw(sprite1);
		}
		else if (currentpage == loginpage)
		{
			window.draw(sprite3);
			if (isusernameactive)
			{
				window.draw(username);
				window.draw(text5);
			}
			else if (ispasswordactive)
			{
				window.draw(username);
				window.draw(pass);
			}
			else
			{
				window.draw(text4);
				window.draw(text5);
			}
			window.draw(Credintials1);
			
			window.draw(Credintials2);
			
			window.draw(text6);

			if (wronginput)
			{
				window.draw(DNE);
			}
		}
		else if (currentpage == greetingpage)
		{
			window.draw(sprite4);
			window.draw(greeting);
			username.setCharacterSize(25);
			username.setPosition(265.f, 250.f);
			window.draw(username);
			window.draw(text3);
			window.draw(text1);
			window.draw(text2);
		}
		else if (currentpage == askpage)
		{
			window.draw(sprite7);
			app.setString("- Appetizers ");
			app.setFillColor(Color(224, 159, 62));
			app.setPosition(10.f, 330.f);
			window.draw(app);
			main.setString("- Main-Course ");
			main.setFillColor(Color(224, 159, 62));
			main.setPosition(10.f, 390.f);
			window.draw(main);
			Dess.setString("- Desserts ");
			Dess.setFillColor(Color(224, 159, 62));
			Dess.setPosition(10.f, 450.f);
			window.draw(Dess);
			Drinks.setString("- Drinks ");
			Drinks.setFillColor(Color(224, 159, 62));
			Drinks.setPosition(10.f, 510.f);
			window.draw(Drinks);
			priv.setString("- Private ");
			priv.setFillColor(Color(224, 159, 62));
			priv.setPosition(10.f, 570.f);
			priv.setCharacterSize(30);
			window.draw(priv);
			window.draw(FL);
		}
		else if (currentpage == appetizerpage)
		{
			window.draw(sprite8);
			app.setString("Appetizers ");
			app.setFillColor(Color::Black);
			app.setPosition(225.f, 400.f);
			window.draw(app);
			LeftArrow.setPosition(130.f, 400.f);
			RightArrow.setPosition(380.f, 400.f);
			window.draw(RightArrow);
			window.draw(LeftArrow);
		}
		else if (currentpage == maincoursepage)
		{
			window.draw(sprite9);
			main.setFillColor(Color::Black);
			main.setPosition(220.f, 400.f);
			main.setString("Main-Course ");
			main.setFillColor(Color::White);
			LeftArrow.setPosition(130.f, 400.f);
			RightArrow.setPosition(408.f, 400.f);
			window.draw(main);
			window.draw(RightArrow);
			window.draw(LeftArrow);
		}
		else if (currentpage == dessertpage)
		{
			window.draw(sprite10);
			Dess.setFillColor(Color::White);
			Dess.setPosition(225.f, 400.f);
			Dess.setString("Desserts");
			window.draw(Dess);
			LeftArrow.setPosition(130.f, 400.f);
			RightArrow.setPosition(370.f, 400.f);
			window.draw(RightArrow);
			window.draw(LeftArrow);
		}
		else if (currentpage == drinkspage)
		{
			window.draw(sprite11);
			Drinks.setFillColor(Color::White);
			Drinks.setPosition(225.f, 400.f);
			Drinks.setString("    Drinks");
			LeftArrow.setPosition(130.f, 400.f);
			RightArrow.setPosition(410.f, 400.f);
			window.draw(Drinks);
			window.draw(RightArrow);
			window.draw(LeftArrow);
		}
		else if (currentpage == recipepage)
		{
			window.draw(sprite5);

			window.draw(textvector[0]);
			
			for (int i = 0; i < allapp[0].size(); i++)
			{
				window.draw(allapp[0][i]);
			}
			LeftArrow.setPosition(220.f, 700.f);
			RightArrow.setPosition(300.f, 700.f);
			window.draw(RightArrow);
			window.draw(LeftArrow);
			
		}
		else if (currentpage == recipepage2)
		{
			window.draw(sprite5);

			window.draw(textvector[1]);

			for (int i = 0; i < allapp[1].size(); i++)
			{
				window.draw(allapp[1][i]);
			}

			
			
			window.draw(LeftArrow);
			window.draw(RightArrow);
		}
		else if (currentpage == recipepage3)
		{
			window.draw(sprite5);

			window.draw(textvector[2]);

			for (int i = 0; i < allapp[2].size(); i++)
			{
				window.draw(allapp[2][i]);
			}
			
			
			window.draw(LeftArrow);
			window.draw(RightArrow);
		}
		else if (currentpage == recipepage4)
		{
			window.draw(sprite5);

			window.draw(textvector[3]);

			for (int i = 0; i < allapp[3].size(); i++)
			{
				window.draw(allapp[3][i]);
			}

			
			
			window.draw(LeftArrow);
			window.draw(RightArrow);
		}
		else if (currentpage == recipepage5)
		{
			window.draw(sprite5);

			window.draw(textvector[4]);

			for (int i = 0; i < allapp[4].size(); i++)
			{
				window.draw(allapp[4][i]);
			}
			
			
			window.draw(LeftArrow);
			window.draw(RightArrow);
		}
		else if (currentpage == recipepage6)
		{
			window.draw(sprite5);

			window.draw(textvector[5]);

			for (int i = 0; i < allapp[5].size(); i++)
			{
				window.draw(allapp[5][i]);
			}

			
			
			window.draw(LeftArrow);
			window.draw(RightArrow);
		}
		else if (currentpage == recipepage7)
		{
			window.draw(sprite5);

			window.draw(textvector[0]);

			for (int i = 0; i < allmain[0].size(); i++)
			{
				window.draw(allmain[0][i]);
			}
			
			LeftArrow.setPosition(220.f, 700.f);
			RightArrow.setPosition(300.f, 700.f);
			window.draw(LeftArrow);
			window.draw(RightArrow);
		}
		else if (currentpage == recipepage8)
		{
			window.draw(sprite5);

			window.draw(textvector[1]);

			for (int i = 0; i < allmain[1].size(); i++)
			{
				window.draw(allmain[1][i]);
			}

			
			window.draw(RightArrow);
			
			window.draw(LeftArrow);
		}
		else if (currentpage == recipepage9)
		{
			window.draw(sprite5);

			window.draw(textvector[2]);

			for (int i = 0; i < allmain[2].size(); i++)
			{
				window.draw(allmain[2][i]);
			}
			
			window.draw(LeftArrow);
		}
		else if (currentpage == recipepage10)
		{
			window.draw(sprite5);

			window.draw(textvector[3]);

			for (int i = 0; i < allmain[3].size(); i++)
			{
				window.draw(allmain[3][i]);
			}

			
			window.draw(RightArrow);
			
			window.draw(LeftArrow);
		}
		else if (currentpage == recipepage11)
		{
			window.draw(sprite5);

			window.draw(textvector[4]);

			for (int i = 0; i < allmain[4].size(); i++)
			{
				window.draw(allmain[4][i]);
			}

			window.draw(RightArrow);
			
			window.draw(LeftArrow);
		}
		else if (currentpage == recipepage12)
		{
			window.draw(sprite5);

			window.draw(textvector[5]);

			for (int i = 0; i < allmain[5].size(); i++)
			{
				window.draw(allmain[5][i]);
			}

			
			window.draw(RightArrow);
			
			window.draw(LeftArrow);
		}
		else if (currentpage == recipepage13)
		{
			window.draw(sprite5);

			window.draw(textvector[0]);

			for (int i = 0; i < alldes[0].size(); i++)
			{
				window.draw(alldes[0][i]);
			}

			LeftArrow.setPosition(220.f, 700.f);
			RightArrow.setPosition(300.f, 700.f);
			window.draw(RightArrow);
			window.draw(LeftArrow);
		}
		else if (currentpage == recipepage14)
		{
			window.draw(sprite5);

			window.draw(textvector[1]);

			for (int i = 0; i < alldes[1].size(); i++)
			{
				window.draw(alldes[1][i]);
			}

			
			window.draw(RightArrow);
			
			window.draw(LeftArrow);
		}
		else if (currentpage == recipepage15)
		{
			window.draw(sprite5);

			window.draw(textvector[2]);

			for (int i = 0; i < alldes[2].size(); i++)
			{
				window.draw(alldes[2][i]);
			}

			
			window.draw(RightArrow);
			
			window.draw(LeftArrow);
		}
		else if (currentpage == recipepage16)
		{
			window.draw(sprite5);

			window.draw(textvector[3]);

			for (int i = 0; i < alldes[3].size(); i++)
			{
				window.draw(alldes[3][i]);
			}

			
			window.draw(RightArrow);
			
			window.draw(LeftArrow);
		}
		else if (currentpage == recipepage17)
		{
			window.draw(sprite5);

			window.draw(textvector[4]);

			for (int i = 0; i < alldes[4].size(); i++)
			{
				window.draw(alldes[4][i]);
			}

			
			window.draw(RightArrow);
			
			window.draw(LeftArrow);
		}
		else if (currentpage == recipepage18)
		{
			window.draw(sprite5);

			window.draw(textvector[5]);

			for (int i = 0; i < alldes[5].size(); i++)
			{
				window.draw(alldes[5][i]);
			}

			
			window.draw(RightArrow);
			
			window.draw(LeftArrow);
		}
		else if (currentpage == recipepage19)
		{
			window.draw(sprite5);

			window.draw(textvector[0]);

			for (int i = 0; i < alldri[0].size(); i++)
			{
				window.draw(alldri[0][i]);
			}

			LeftArrow.setPosition(220.f, 700.f);
			RightArrow.setPosition(300.f, 700.f);
			window.draw(RightArrow);
			window.draw(LeftArrow);
		}
		else if (currentpage == recipepage20)
		{
			window.draw(sprite5);

			window.draw(textvector[1]);

			for (int i = 0; i < alldri[1].size(); i++)
			{
				window.draw(alldri[1][i]);
			}

			
			window.draw(RightArrow);
			
			window.draw(LeftArrow);
		}
		else if (currentpage == recipepage21)
		{
			window.draw(sprite5);

			window.draw(textvector[2]);

			for (int i = 0; i < alldri[2].size(); i++)
			{
				window.draw(alldri[2][i]);
			}

			window.draw(RightArrow);
			window.draw(LeftArrow);
		}
		else if (currentpage == recipepage22)
		{
			window.draw(sprite5);

			window.draw(textvector[3]);

			for (int i = 0; i < alldri[3].size(); i++)
			{
				window.draw(alldri[3][i]);
			}
			window.draw(RightArrow);
			window.draw(LeftArrow);
		}
		else if (currentpage == recipepage23)
		{
			window.draw(sprite5);

			window.draw(textvector[4]);

			for (int i = 0; i < alldri[4].size(); i++)
			{
				window.draw(alldri[4][i]);
			}

			window.draw(RightArrow);
			window.draw(LeftArrow);
		}
		else if (currentpage == recipepage24)
		{
			window.draw(sprite5);

			window.draw(textvector[5]);

			for (int i = 0; i < alldri[5].size(); i++)
			{
				window.draw(alldri[5][i]);
			}

			window.draw(RightArrow);
			window.draw(LeftArrow);
		}
		else if (currentpage == recipepage25)
		{
			window.draw(sprite5);
			window.draw(p);
			for (int i = 0; i < privatenamesfromcustom[usercount].size(); i++)
			{
				window.draw(privatenamesfromcustom[usercount][i]);
			}

		}
		else if (currentpage == recipeprintingpage)
		{
			window.draw(sprite6);
			window.draw(get);
			Ing.setFillColor(Color::White);
			Ing.setOutlineThickness(3.f);
			Ing.setPosition(50, 50);
			window.draw(Ing);
			RightArrow.setPosition(300.f, 830.f);
			LeftArrow.setPosition(20.f, 830.f);
			window.draw(LeftArrow);
			window.draw(RightArrow);

			for (int i = 0; i < recipeprintingIng.size(); i++)
			{
				window.draw(recipeprintingIng[i]);
			}
		}
		else if (currentpage == recipeprintingpage2)
		{
			window.draw(sprite6);
			window.draw(get);
			window.draw(Ins);
			window.draw(LeftArrow);
			for (int i = 0; i < recipeprintingIns.size(); i++)
			{
				window.draw(recipeprintingIns[i]);
			}
		}
		else if (currentpage == recipeinput)
		{
			window.draw(sprite2);
			window.draw(In);

			if (isCuisinenameactive)
			{
				window.draw(Cuisinenameshort);
				window.draw(Cname);
			}
			else if(!typeselectionflag && !isrecipenameactive)
			{
				window.draw(Cuisinename);
				typeselection.setPosition(152.f, 242.f);
				window.draw(typeselection);
				float p = 270.f;
				for (int i = 0; i < textvector.size(); i++)
				{
					textvector[i].setFillColor(Color::White);
					textvector[i].setPosition(152.f, p);
					p += 30.f;
					textvector[i].setCharacterSize(20);
				}
				for (int i = 0; i < textvector.size(); i++)
				{
					window.draw(textvector[i]);
				}
			}

			if (typeselectionflag)
			{
				window.draw(RecipeFoodTypeshort);
				window.draw(typedisplay);
				window.draw(RecipeNAME);
				
			}
			else if(!typeselectionflag && isCuisinenameactive)
			{
				typeselection.setFillColor(Color::White);
				typeselection.setPosition(152.f, 285.f);
				window.draw(RecipeFoodType);
				window.draw(typeselection);
				window.draw(ap);
				window.draw(ma);
				window.draw(Dr);
				window.draw(De);
			}

			if (isrecipenameactive)
			{
				window.draw(Rname);
			}
			else if(!isrecipenameactive && typeselectionflag)
			{
				window.draw(rname);
			}
			if (donerecipe)
			{
				RightArrow.setPosition(420.f, 650.f);
				window.draw(RightArrow);
				window.draw(forIngarrow);
			}
		}
		else if (currentpage == recipeinput2)
		{
			window.draw(sprite2);
			window.draw(In);
			window.draw(IngInput);
			window.draw(RightArrow);
			if (isingactive)
			{
				window.draw(IGinputdup);
				window.draw(IGinput);
			}
			else
			{
				window.draw(IG);
			}
		}
		else if (currentpage == recipeinput3)
		{
			window.draw(sprite2);
			window.draw(In);
			window.draw(IngInput);
			window.draw(RightArrow);
			if (isinsactive)
			{
				window.draw(ISinputdup);
				window.draw(ISinput);
			}
			else
			{
				window.draw(IS);
			}
		}
		else if (currentpage == recipesubmitted)
		{
			window.draw(sprite2);
			window.draw(In);
			
			if (wantprivate || wantpublic)
			{
				
				string Ingi;
				string Inst;
				string Ingitemp;
				string Insttemp;

				for (int i = 0; i < customiginput.size(); i++)
				{
					Ingitemp = customiginput[i].getString().toAnsiString();

					for (int j = 0; j < Ingitemp.length(); j++)
					{
						if (Ingitemp[j] == ' ')
						{
							Ingi += "-";
						}
						else
						{
							Ingi += Ingitemp[j];
						}
					}
					Ingi += " ";
				}

				for (int i = 0; i < customisinput.size(); i++)
				{
					Insttemp = customisinput[i].getString().toAnsiString();

					for (int j = 0; j < Insttemp.length(); j++)
					{
						if (Insttemp[j] == ' ')
						{
							Inst += "-";
						}
						else
						{
							Inst += Insttemp[j];
						}
					}
					Inst += " ";
				}

				queue <string> QR;

				QR.push(Cname.getString().toAnsiString());
				QR.push(typedisplay.getString().toAnsiString());
				QR.push(Rname.getString().toAnsiString());
				QR.push(Ingi);
				QR.push(Inst);

				if (wantpublic)
				{
					fileinsertionpublic(QR);
				}
				else if (wantprivate)
				{
					fileinsertionprivate(QR, usercount, currentcount);
				}

				currentpage = thankyou;
			}
			else
			{
				window.draw(pri);
				window.draw(privacy);
				window.draw(pub);
				window.draw(priv);
			}
		}
		else if (currentpage == thankyou)
		{
			window.draw(sprite2);
			window.draw(ty);
			window.draw(LeftArrow);
		}
		else if (currentpage == flpage)
		{
			window.draw(sprite14);
			app.setString("  Appetizers ");
			app.setFillColor(Color::White);
			app.setPosition(200.f, 330.f);
			window.draw(app);
			main.setString("Main-Course ");
			main.setFillColor(Color::White);
			main.setPosition(200.f, 390.f);
			window.draw(main);
			Dess.setString("    Desserts ");
			Dess.setFillColor(Color::White);
			Dess.setPosition(200.f, 450.f);
			window.draw(Dess);
			Drinks.setString("    Drinks ");
			Drinks.setFillColor(Color::White);
			Drinks.setPosition(200.f, 510.f);
			window.draw(Drinks);
		}
		else if (currentpage == flrecipenamepage)
		{
			window.draw(sprite14);
			Text t("You Should Have: \n" + flrecipename, font3, 30);
			t.setFillColor(Color::White);
			t.setPosition(175.f, 400.f);
			window.draw(t);
			LeftArrow.setPosition(220.f, 650.f);
			RightArrow.setPosition(300.f, 650.f);
			window.draw(RightArrow);
			window.draw(LeftArrow);
		}
		
		window.display();
	}

	return 0;
}