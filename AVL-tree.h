#include<iostream>

struct AVLNode 
{
	int key;
	int value;
	int height;
	AVLNode *left;
	AVLNode *right;
};

class AVLTree 
{
public:
	AVLTree();
	~AVLTree();

	int Min();
	int Max();

	int Search(int key);
	void Insert(int, int);
	bool Delete(int key);

	void PrintPreOrder(std::ostream &);
	
private:
	AVLNode *root;
	AVLNode *NIL;

	void GetHeight(AVLNode *N);

	int SearchOne(AVLNode *temp, int key);
	AVLNode* Exist(AVLNode *temp, int key);
	AVLNode* InsertOne(AVLNode *temp, int key, int value);
	AVLNode* DeleteOne(AVLNode *temp, int key);
	AVLNode* RotateLeft(AVLNode *temp);
	AVLNode* RotateRight(AVLNode *temp);
	AVLNode* Balance(AVLNode *temp);

	void PrintPreOrderOne(std::ostream &, AVLNode *temp);
	
	void DeallocMemory(AVLNode *temp);
};


AVLTree::AVLTree() 
{
	root = NIL = new AVLNode;
	NIL->height = 0;
	NIL->left = NIL->right = nullptr;
}


AVLTree::~AVLTree() {
	DeallocMemory(root);
}

int AVLTree::Min()
{
	AVLNode *N = root;
	while (N->left != NIL) N = N->left;
	return N->value;
}

int AVLTree::Max()
{
	AVLNode *N = root;
	while (N->right != NIL)
	{
		N = N->right;
	}
	return N->value;
}

int AVLTree::SearchOne(AVLNode *temp, int key)
{
	if (temp == NIL) 
	{
		return 0;
	}

	if (temp->key == key) 
	{
		return temp->value;
	}

	if (key < temp->key) 
	{
		return SearchOne(temp->left, key);
	}
	else
	{
		return SearchOne(temp->right, key);
	}
}

int AVLTree::Search(int key) 
{
	if (root == NIL) 
	{
		return 0;
	}

	if (root->key == key) 
	{
		return root->value;
	}

	if (key < root->key) 
	{
		return SearchOne(root->left, key);
	}
	else 
	{
		return SearchOne(root->right, key);
	}
}

void AVLTree::PrintPreOrder(std::ostream &outputstream) 
{
	PrintPreOrderOne(outputstream, root);
}

void AVLTree::GetHeight(AVLNode *N) 
{
	N->height = 1 + N->left->height > N->right->height ? N->left->height : N->right->height;
}

AVLNode *AVLTree::RotateLeft(AVLNode *temp) 
{
	AVLNode *t = temp->left;
	temp->left = t->right;
	t->right = temp;
	GetHeight(temp);
	GetHeight(t);

	return t;
}

AVLNode *AVLTree::RotateRight(AVLNode *temp) 
{
	AVLNode *N = temp->right;
	temp->right = N->left;
	N->left = temp;
	GetHeight(temp);
	GetHeight(N);

	return N;
}

AVLNode *AVLTree::InsertOne(AVLNode *temp, int key, int value) 
{
	if (temp == NIL) 
	{
		temp = new AVLNode;
		temp->key = key;
		temp->value = value;
		temp->left = temp->right = NIL;
		temp->height = 1;

		return temp;
	}

	if (key <= temp->key) 
	{
		temp->left = InsertOne(temp->left, key, value);
	}
	else 
	{
		temp->right = InsertOne(temp->right, key, value);
	}

	return Balance(temp);
}

void AVLTree::Insert(int key, int value) 
{
	root = InsertOne(root, key, value);
}

AVLNode *AVLTree::DeleteOne(AVLNode *temp, int key) 
{
	AVLNode *t;
	if (temp == NIL)
	{
		return temp;
	}
	if (temp->key == key) 
	{
		if (temp->left == NIL || temp->right == NIL) 
		{
			if (temp->left == NIL) 
			{
				t = temp->right;
			}
			else 
			{
				t = temp->left;
			}
			delete temp;
			return t;
		}
		else 
		{
			for (t = temp->right; t->left != NIL; t = t->left);
			temp->key = t->key;
			temp->right = DeleteOne(temp->right, t->key);
			return Balance(temp);
		}
	}

	if (key < temp->key) 
	{
		temp->left = DeleteOne(temp->left, key);
	}
	else

	{
		temp->right = DeleteOne(temp->right, key);
	}

	return Balance(temp);
}

bool AVLTree::Delete(int key)
{
	if (Exist(root, key))
	{
		root = DeleteOne(root, key);
		return true;
	}
	return false;
}

AVLNode *AVLTree::Balance(AVLNode *temp) 
{
	GetHeight(temp);

	if (temp->left->height > temp->right->height + 1) 
	{
		if (temp->left->right->height > temp->left->left->height)
		{
			temp->left = RotateRight(temp->left);
		}
		temp = RotateLeft(temp);
	}
	else if (temp->right->height > temp->left->height + 1) 
	{
		if (temp->right->left->height > temp->right->right->height) 
		{
			temp->right = RotateLeft(temp->right);
		}
		temp = RotateRight(temp);
	}

	return temp;
}

void AVLTree::PrintPreOrderOne(std::ostream &outputstream, AVLNode *temp) 
{
	if (temp == NIL) 
	{
		return;
	}
	outputstream << temp->value << " ";
	PrintPreOrderOne(outputstream, temp->left);
	PrintPreOrderOne(outputstream, temp->right);
}

void AVLTree::DeallocMemory(AVLNode *temp) 
{
	if (temp == NIL) 
	{
		return;
	}
	DeallocMemory(temp->left);
	DeallocMemory(temp->right);
	delete temp;
}

AVLNode *AVLTree::Exist(AVLNode *temp, int key) 
{
	if (temp == NIL)
	{
		return nullptr;
	}

	if (temp->key == key)
	{
		return temp;
	}

	if (key < temp->key)
	{
		return Exist(temp->left, key);
	}
	else 
	{
		return Exist(temp->right, key);
	}
}
