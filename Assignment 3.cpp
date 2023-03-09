//************************************************************************** 
//
// Programming Excerise 3   
// CLASS: COSC 2336.S01
// AUTHOR: TYLER ECHOLS 
// DAtE: Oct 2017  
//
//************************************************************************** 

#include <iostream>

using namespace std;

#include "RAFiles.h"

void main()
{

	RAFiles			File;

	string kbInput;
	string stringInput;
	string stringInput2;
	string command;
	int inputLength;
	int indexInput;
	int spaceInput;
	string s;

	File.Openfile("NotHereFile.txt");
	File.Insert(0, "hello");
	File.Insert(1, "I'm late");
	File.Insert(1, "Goodbye");
	File.Insert(2, "I'm late");
	File.Insert(3, "I'm late!");
	File.Replace(1, "Wonderland");

	File.Replace(4, "Alice In Wonderland");
	File.Insert(15, "Why is a raven like a writing desk?");
	File.Replace(25, "Painting the roses red");

	cout << "Commands: \nG integer - prints out the integer at this index\nR integer string - replaces the typed index with the new string\nI integer string - inserts the typed string at the typed index\nX - Terminates the program\n\n" << endl;

	while (command != "X")
	{
		cout << "Please enter a command: ";
		getline(cin, kbInput);
		inputLength = kbInput.length();

		if (inputLength != 0) //checks if there is any user input
		{
			command = kbInput.at(0);
		}
		else //if there is no user input, prevents at from throwing an exception. sets to an impossible value. 
		{
			command = " ";
		}

		if (command == "G")
		{
			if ((kbInput.length() > 2) && (kbInput.at(1) == ' '))
			{
				stringInput = kbInput.substr(2); //gets a substring from position 2 to the end
				indexInput = atoi(stringInput.c_str());
				if (indexInput < 0 || indexInput >= File.size())
				{
					cout << "Invalid index" << endl;
				}
				else
				{
					File.Get(indexInput, s);
					cout << "The string at index " << stringInput << " is " << s << endl;
				}
			}
			else
			{
				cout << "Invalid command" << endl;
			}
		}
		else
		{
			if (command == "R")
			{
				if ((kbInput.length() > 4) && (kbInput.at(1) == ' ') && ((kbInput.find(" ", 3) != -1)))//checks for at least the minimum number of characters, and if they entered the first space.
				{
					spaceInput = kbInput.find(" ", 3);
					stringInput = kbInput.substr(2, spaceInput - 1); //the string containing the integer for the index
					indexInput = atoi(stringInput.c_str());
					stringInput2 = kbInput.substr(spaceInput + 1); //the string that will be written to the file. 
					if (indexInput >= 0)
					{
						File.Replace(indexInput, stringInput2);
						cout << "Replaced position " << indexInput << " with " << stringInput2 << endl;
					}
					else
					{
						cout << "Invalid index" << endl;
					}
				}
				else
				{
					cout << "Invalid command" << endl;
				}
			}
			else
			{
				if (command == "I")
				{
					if ((kbInput.length() > 4) && (kbInput.at(1) == ' ') && ((kbInput.find(" ", 3) != -1)))//checks for at least the minimum number of characters, and if they entered the first space.
					{
						spaceInput = kbInput.find(" ", 3);
						stringInput = kbInput.substr(2, spaceInput - 1); //the string containing the integer for the index
						indexInput = atoi(stringInput.c_str());
						stringInput2 = kbInput.substr(spaceInput + 1); //the string that will be written to the file. 
						if (indexInput >= 0)
						{
							File.Insert(indexInput, stringInput2);
							cout << "Inserted " << stringInput2 << " at " << indexInput << endl;
						}
						else
						{
							cout << "Invalid index" << endl;
						}
					}
					else
					{
						cout << "Invalid command" << endl;
					}
				}
				else
				{
					if (command == "X")
					{
						cout << "Terminating program" << endl;
					}
					else
					{
						cout << "Invalid command" << endl;
					}
				}
			}
		}
	}
	File.Closefile();
}