#include "stdafx.h"
#include <iostream>
#include "../new_dz_algorithms-and-dataStructures/AVL-tree.h"

int main() {
	AVLTree<int> avltree;
	avltree.Insert(1, 3);
	avltree.Insert(2, 12);
	avltree.Insert(3, 2345);
	avltree.Insert(4, 534);
	avltree.Insert(5, 76);
	avltree.Insert(6, 90);
	avltree.PrintPreOrderTraversal(std::cout);
	std::cout << std::endl;
	std::cout << avltree.SearchValue(3);
	system("pause");
	return 0;
}
