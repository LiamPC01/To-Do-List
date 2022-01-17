// Add, delete and save tasks to the To-Do List

#include "Header.h"

int main()
{
	char input;
	getList();
	std::cout << "TO-DO LIST\n"
		<< "__________\n";
	printList();
	std::cout << "\nEnter \'A\' to add another task\nEnter \'D\' to delete a task"
		<< "\nEnter \'E\' to save and exit:\n";
	std::cin >> input;
	if (input == 'a' || input == 'A')
	{
		addToList();
	}
	else if (input == 'd' || input == 'D')
	{
		delLine();
	}
	else if (input == 'e' || input == 'E')
	{
		saveList();
	}
}

void getList()
{
	std::string line;
	std::ifstream inFile("tasks.txt"); // Opens items.txt
	if (!inFile.is_open())
	{
		std::cerr << "Error Opening items.txt\n";
	}

	while (getline(inFile, line))
	{
		if (!line.empty())
		{
			line += "\n";
			listOfTasks.push_back(line); // Push all lines with text in .txt to listOfTasks 
		}
	}
	inFile.close();
}

void printList()
{
	for (int i = 0; i < listOfTasks.size(); i++)
	{
		std::cout << i + 1 << ": "; // Line number
		std::cout << listOfTasks[i];
	}
}

void addToList()
{
	std::string newTask;

	std::cout << "\nEnter the task you wish to add:\n";
	std::cin.ignore(1); // .ignore '\n' from cin
	getline(std::cin, newTask);
	std::cout << '\n';

	newTask += "\n";
	listOfTasks.push_back(newTask); // push newTask to listOfTasks

	main();
}

void delLine()
{
	int delNum;

	std::cout << "\nEnter the line number of the task you wish to delete:\n";
	std::cin >> delNum;

	delNum -= 1; // 0 based index
	listOfTasks.erase(listOfTasks.begin() + delNum); // Delete line from vector

	main();
}

void saveList()
{
	std::ofstream("tasks.txt", std::ofstream::trunc); // clear all tasks in .txt

	std::ofstream outFile("tasks.txt", std::ios::app);
	for (int i = 0; i < listOfTasks.size(); i++)
	{
		outFile << listOfTasks[i]; // Update .txt with new tasks
	}

	outFile.close();
}

