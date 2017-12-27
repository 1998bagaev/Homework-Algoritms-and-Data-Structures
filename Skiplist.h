#include <iostream>

const int MAXLEVEL = 20;

struct skiplist_node 
{
	explicit skiplist_node(int searchKey);
	explicit skiplist_node(int key,int value);
	int key, value;
	skiplist_node* forwards[MAXLEVEL + 1];

};

class skiplist 
{

public:

	skiplist();
	~skiplist();

	void Add(int key,int value);
	bool Remove(int searchKey);
	bool Search(int searchKey);
	int Max();
	int Min();
	void printList(std::ostream &outputstream);

	const int max_level;

private:

	double uniformRandom() 
	{ return rand() / double(RAND_MAX); }

	int randomLevel();
	int m_minKey;
	int m_maxKey;
	int max_curr_level;
	skiplist_node* m_pHeader;
	skiplist_node* m_pTail;
	
};

skiplist_node::skiplist_node(int searchKey)
{

	key = searchKey;

	for (int i = 1; i <= MAXLEVEL; i++) { forwards[i] = nullptr; }

}


skiplist_node::skiplist_node(int _key,int _value) :key(_key), value(_value) 
{

	for (int i = 1; i <= MAXLEVEL; i++) { forwards[i] = nullptr; }

}

skiplist::skiplist() :m_pHeader(nullptr), m_pTail(nullptr),
max_curr_level(1), max_level(20),
m_minKey(0), m_maxKey(10000) {

	m_pHeader = new skiplist_node(m_minKey);
	m_pTail = new skiplist_node(m_maxKey);

	for (int i = 1; i <= MAXLEVEL; i++) { m_pHeader->forwards[i] = m_pTail; }

}

skiplist::~skiplist() 
{

	skiplist_node* currNode = m_pHeader->forwards[1];

	while (currNode != m_pTail) {

		skiplist_node* tempNode = currNode;
		currNode = currNode->forwards[1];

		delete tempNode;
	}

	delete m_pHeader;

	delete m_pTail;
}

void skiplist::Add(int key,int value)
{

	skiplist_node* update[MAXLEVEL];
	skiplist_node* currNode = m_pHeader;

	for (int level = max_curr_level; level >= 1; level--) {

		while (currNode->forwards[level]->key < key) { currNode = currNode->forwards[level]; }

		update[level] = currNode;

	}

	currNode = currNode->forwards[1];

	if (currNode->key == key) { currNode->value = value; }

	else {

		int newlevel = randomLevel();

		if (newlevel > max_curr_level) {

			for (int level = max_curr_level + 1; level <= newlevel; level++) { update[level] = m_pHeader; }

			max_curr_level = newlevel;

		}

		currNode = new skiplist_node(key,value);

		for (int lv = 1; lv <= max_curr_level; lv++) {

			currNode->forwards[lv] = update[lv]->forwards[lv];
			update[lv]->forwards[lv] = currNode;

		}
	}
}


bool skiplist::Remove(int searchKey) 
    {

	if (!Search(searchKey)) { return false; }

	skiplist_node* update[MAXLEVEL];
	skiplist_node* currNode = m_pHeader;

	for (int level = max_curr_level; level >= 1; level--) 
	{

		while (currNode->forwards[level]->key < searchKey) 
		{ 
			currNode = currNode->forwards[level]; 
		}

		update[level] = currNode;

	}

	currNode = currNode->forwards[1];

	if (currNode->key == searchKey) 
	{

		for (int lv = 1; lv <= max_curr_level; lv++)
		{

			if (update[lv]->forwards[lv] != currNode) { break; }

			update[lv]->forwards[lv] = currNode->forwards[lv];

		}

		delete currNode;


		while (max_curr_level > 1 && m_pHeader->forwards[max_curr_level] == nullptr) { max_curr_level--; }

	}

	return true;
}


bool skiplist::Search(int searchKey)
{

	skiplist_node* currNode = m_pHeader;

	for (int level = max_curr_level; level >= 1; level--) 
	{

		while (currNode->forwards[level]->key < searchKey) 
		{ currNode = currNode->forwards[level]; }

	}

	currNode = currNode->forwards[1];

	return currNode->key == searchKey;

}


int skiplist::randomLevel() 
{

	int level = 1;
	double p = 0.5;

	while (uniformRandom() < p && level < MAXLEVEL) 
	{ level++; }

	return level;

}

void skiplist::printList(std::ostream &outputstream) 
{

	skiplist_node* currNode = m_pHeader->forwards[1];

	while (currNode != m_pTail) 
	{

		outputstream << currNode->value << " ";
		currNode = currNode->forwards[1];

	}
	//outputstream << std::endl;
}

int skiplist::Max() 
{

	int max = -1;
	skiplist_node* currNode = m_pHeader;

	for (int level = max_curr_level; level >= 1; level--)
	{

		while (currNode->forwards[level]) 
		{

			if (currNode->value > max) { max = currNode->value; }
		}
	}

	return max;

};

int skiplist::Min() 
{

	int min = INT_MAX;
	skiplist_node* currNode = m_pHeader;

	for (int level = max_curr_level; level >= 1; level--) 
	{

		while (currNode->forwards[level]) 
		{

			if (currNode->value < min) { min = currNode->value; }
		}
	}

	return  min;

};




