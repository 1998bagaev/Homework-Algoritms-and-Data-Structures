#include "stdafx.h"
#include <iostream>
#include <cassert>
#include <sstream>
#include <fstream>
#include <ctime>

#include "AVL-tree.h"
#include "Skiplist.h"

int FindKey(const std::string &str)
{
	std::istringstream iss(str);
	std::string tmp;
	iss >> tmp;
	tmp.clear();
	iss >> tmp;
	int key = atoi(tmp.c_str());
	return key;
}

int FindValue(const std::string &str) 
{
	std::istringstream iss(str);
	std::string tmp;
	iss >> tmp;
	tmp.clear();
	iss >> tmp;
	tmp.clear();
	iss >> tmp;
	int value = atoi(tmp.c_str());
	return value;
}

bool FileIsEqual(const std::string &firstFileName, const std::string &secondFileName) 
{
	std::ifstream firstFile(firstFileName), secondFile(secondFileName);
	assert(firstFile);
	assert(secondFile);

	std::string buffer1((std::istreambuf_iterator<char>(firstFile)), std::istreambuf_iterator<char>());
	std::string buffer2((std::istreambuf_iterator<char>(secondFile)), std::istreambuf_iterator<char>());
	firstFile.close();
	secondFile.close();

	return (buffer1 == buffer2);
}


int main(int argc, char* argv[]) 
{
	if (argc < 4)
	{
		return 0;
	}
	std::string line;
	std::ifstream fileIn(argv[0]);
	assert(fileIn);
	std::ofstream fileOut(argv[1]);
	assert(fileOut);

	AVLTree avlTree;

	srand(time(0));

	while (getline(fileIn, line)) 
	{
		if (line.find("delete") == 0) 
		{
						
				if (!avlTree.Delete(FindKey(line))) 
				{
					fileOut << "error" << std::endl;
				}
				else
				{
					fileOut << "Ok" << std::endl;
				}

			
		}
		if (line == "print") 
		{
			avlTree.PrintPreOrder(fileOut);
			fileOut << std::endl;
		}
		if (line.find("add") == 0) 
		{
			avlTree.Insert(FindKey(line), FindValue(line));
		}
		if (line.find("search") == 0)
		{
			fileOut << avlTree.Search(FindKey(line)) << std::endl;
		}
		if (line == "min")
		{
			fileOut << avlTree.Min() << std::endl;
		}
		if (line == "max") 
		{
			fileOut << avlTree.Max() << std::endl;
		}
		if (line == " ") 
		{
			fileOut << "error" << std::endl;
		}
	}

	std::cout << "runtime = " << clock() / 1000.0 << std::endl;

	if (FileIsEqual(argv[1], argv[2])) 
	{
		std::cout << "Correct" << std::endl;
	}
	else 
	{
		std::cout << "Not correct" << std::endl;
	}


	fileIn.clear();
	fileIn.seekg(0);
	fileOut.clear();
	fileOut.seekp(0);

	skiplist object;

	srand(time(0));

	while (getline(fileIn, line)) 
	{
		if (line.find("delete") == 0) 
		{
			
				if (!object.Remove(FindKey(line))) 
				{
					fileOut << "error" << std::endl;
				}
				else 
				{
					fileOut << "Ok" << std::endl;
				}
			
		}
		if (line == "print") 
		{
			object.printList(fileOut);
			fileOut << std::endl;
		}
		if (line.find("add") == 0)
		{
			object.Add(FindKey(line), FindValue(line));
		}
		if (line.find("search") == 0)
		{
			fileOut << object.Search(FindKey(line)) << std::endl;
		}
		if (line == "min") 
		{
			fileOut << object.Min() << std::endl;
		}
		if (line == "max")
		{
			fileOut << object.Max() << std::endl;
		}
		if (line == " ")
		{
			fileOut << "error" << std::endl;
		}
	}

	std::cout << "runtime = " << clock() / 1000.0 << std::endl;

	if (FileIsEqual(argv[1], argv[2]))
	{
		std::cout << "Correct" << std::endl;
	}
	else 
	{
		std::cout << "Not correct" << std::endl;
	}

	fileIn.close();
	fileOut.close();

	system("pause");
	return 0;
	
	
}
