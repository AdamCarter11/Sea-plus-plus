#include "pch.h"
#include <iostream>
#include "Tree.h"
using namespace std;
int main() {
	Tree<int> myTree;
	myTree.insertNode(15);
	myTree.insertNode(34);
	myTree.insertNode(17);
	myTree.insertNode(5);
	myTree.insertNode(2);
	myTree.insertNode(10);
	myTree.insertNode(23);
	myTree.insertNode(30);
	//myTree.insertNode(17);

	myTree.displayNode();
	myTree.postDisplayNode();
	myTree.inOrderDisplayNode();

	cout <<endl<< "--------------------";

	//should return 4
	myTree.height();
	//should return 9
	myTree.size();
	//should return 8
	myTree.min();
	//should return 40
	myTree.max();

	//myTree.removeNode(13);

	cout << endl << "end" << endl;;
}