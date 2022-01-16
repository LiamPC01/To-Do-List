// This program must allow the user to add tasks, remove tasks and view tasks

#include "Header.h"

int main()
{
	checkNumOrder();
	getLineNum();
	char input;
	std::cout << "TO-DO LIST\n"
		<< "__________\n";
	printList();
	std::cout << "\nEnter \'A\' to add another task or enter \'D\' to delete a task:\n";
	std::cin >> input;
	if (input == 'a' || input == 'A')
	{
		addTask();
	}
	else if (input == 'd' || input == 'D')
	{
		delTask();
	}
}

void checkNumOrder()
{
	// Open file
	std::ifstream inFile("tasks.txt");
	std::string line;

	if (inFile.peek() != std::ifstream::traits_type::eof()) // If file not empty
	{
		// Push lineNums to listOfNums
		while (getline(inFile, line))
		{
			lineNum = line[0] - '0'; // Converts from char to int
			listOfNums.push_back(lineNum);
		}

		// Shows vector positon of each num before sort for debugging
		std::cout << "listOfNums before sorting:\n";
		for (int blah = 0; blah < listOfNums.size(); blah++)
		{
			std::cout << "listOfNums[" << blah << "] = " << listOfNums[blah] << "\n";
		}

		// Compare num to next num
		int prevLineNum = 0;
		for (int nextLineNum = 1; nextLineNum < listOfNums.size(); nextLineNum++)
		{
			// While difference between prevLineNum and nextLineNum is greater than 1
			while (listOfNums[nextLineNum] > listOfNums[prevLineNum] + 1)
			{
				// Decrement
				listOfNums[nextLineNum]--;
			}
			prevLineNum++;

		}
		std::cout << "listOfNums after sorting:\n";
		for (int blah = 0; blah < listOfNums.size(); blah++)
		{
			std::cout << "listOfNums[" << blah << "] = " << listOfNums[blah] << "\n";
		}
	}

}



void getLineNum()
{
	//lineNum = listOfNums.size() + 1;
	
	
	//check list for last num
	std::ifstream inFile("tasks.txt");
	std::string line;

	if (line.empty())
	{
		lineNum = 1;
	}

	while (getline(inFile, line))
	{
		char lastNum;
		lastNum = line[0];
		lastNum -= '0'; // converts from char to int
		lineNum = lastNum + 1;
	}
	
}

void printList()
{
	std::string line;
	// Opens items.txt
	std::ifstream inFile("tasks.txt");
	if (!inFile.is_open())
	{
		std::cerr << "Error Opening items.txt\n";
	}

	while (!inFile.eof()) // While not at end of file
	{
		getline(inFile, line);
		if (!line.empty())
		{
			std::cout << line << "\n";
		}
	}
	inFile.close();
}

void addTask()
{

	std::string task;

	// Opens items.txt
	std::ofstream oFile("tasks.txt", std::ios::app);
	if (!oFile.is_open())
	{
		std::cerr << "Error Opening items.txt\n";
	}

	std::cout << "\nEnter the task you wish to add:\n";
	std::cin.ignore(1); // .ignore '\n' from cin
	getline(std::cin, task);
	std::cout << '\n';

	task.insert(0, std::to_string(lineNum)); // Inserts lineNum at start line
	task.insert(1, ": ");
	lineNum++;

	oFile << task << '\n';
	oFile.close();
	main();
}

void delTask()
{
	char delChar;
	std::cout << "\nEnter the line number of the task you wish to delete:\n";
	std::cin >> delChar;

	// Copy all lines to temp.txt except the one to delete
	std::ifstream oldFile("tasks.txt");
	std::string line;
	std::ofstream newFile("temp.txt", std::ios::app);
	while (getline(oldFile, line))
	{
		if (line[0] != delChar)
		{

			newFile << line << '\n';

		}
	}
	oldFile.close();
	newFile.close();

	std::ofstream delTasks("tasks.txt", std::ofstream::trunc); // Erasing tasks.txt

	std::ifstream inFile("temp.txt");
	while (getline(inFile, line))
	{
		std::ofstream outFile("tasks.txt", std::ios::app);
		outFile << line << '\n'; // Copy temp into tasks.txt

	}
	std::ofstream delTemp("temp.txt", std::ofstream::trunc); // Erasing temp.tx
	main();
}