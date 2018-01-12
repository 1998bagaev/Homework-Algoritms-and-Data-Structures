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
	if (argc < 6)
	{
		return 0;
	}
	std::string line;
	std::ifstream fileIn(argv[1]);
	assert(fileIn);
	std::ofstream fileOutAVL(argv[2]);
	assert(fileOutAVL);
	std::ofstream fileOutSkip(argv[3]);
	assert(fileOutSkip);
	

	AVLTree avlTree;

	srand(time(0));

	while (getline(fileIn, line)) 
	{
		if (line.find("delete") == 0) 
		{
						
				if (!avlTree.Delete(FindKey(line))) 
				{
					fileOutAVL << "error" << std::endl;
				}
				else
				{
					fileOutAVL << "Ok" << std::endl;
				}

			
		}
		if (line == "print") 
		{
			avlTree.PrintPreOrder(fileOutAVL);
			fileOutAVL << std::endl;
		}
		if (line.find("add") == 0) 
		{
			avlTree.Insert(FindKey(line), FindValue(line));
		}
		if (line.find("search") == 0)
		{
			fileOutAVL << avlTree.Search(FindKey(line)) << std::endl;
		}
		if (line == "min")
		{
			fileOutAVL << avlTree.Min() << std::endl;
		}
		if (line == "max") 
		{
			fileOutAVL << avlTree.Max() << std::endl;
		}
		if (line == " ") 
		{
			fileOutAVL << "error" << std::endl;
		}
	}

	std::cout << "runtime = " << clock() / 1000.0 << std::endl;

	if (FileIsEqual(argv[2], argv[4])) 
	{
		std::cout << "Correct" << std::endl;
	}
	else 
	{
		std::cout << "Not correct" << std::endl;
	}

	
	fileIn.clear();
	fileIn.seekg(0);
	
	
	skiplist object;

	srand(time(0));

	while (getline(fileIn, line)) 
	{
		if (line.find("delete") == 0) 
		{
			
				if (!object.Remove(FindKey(line))) 
				{
					fileOutSkip << "error" << std::endl;
				}
				else 
				{
					fileOutSkip << "Ok" << std::endl;
				}
			
		}
		if (line == "print") 
		{
			object.printList(fileOutSkip);
			fileOutSkip << std::endl;
		}
		if (line.find("add") == 0)
		{
			object.Add(FindKey(line), FindValue(line));
		}
		if (line.find("search") == 0)
		{
			fileOutSkip << object.Search(FindKey(line)) << std::endl;
		}
		if (line == "min") 
		{
			fileOutSkip << object.Min() << std::endl;
		}
		if (line == "max")
		{
			fileOutSkip << object.Max() << std::endl;
		}
		if (line == " ")
		{
			fileOutSkip << "error" << std::endl;
		}
	}

	std::cout << "runtime = " << clock() / 1000.0 << std::endl;

	if (FileIsEqual(argv[3], argv[5]))
	{
		std::cout << "Correct" << std::endl;
	}
	else 
	{
		std::cout << "Not correct" << std::endl;
	}
	
	fileIn.close();
	fileOutAVL.close();
	fileOutSkip.close();

	system("pause");
	return 0;
	
	
}
