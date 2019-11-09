#ifndef Tree_h
#define Tree_h
#include "TreeNode.h"
#include <iostream>
#include <cstdlib>
template<typename NODETYPE>
class Tree {
private:
	TreeNode<NODETYPE>* rootPtr;
	//line below is creating the helper function, and it needs to take in a ptr of a ptr
	//This means that we are pointing at a pointer (headPtr->rightPtr->childOfRightPtr)
	//similarly to a tree with branches
	void insertNodeHelper(TreeNode<NODETYPE>**, const NODETYPE&);
	int removeNodeHelper(TreeNode<NODETYPE>**,  const NODETYPE&);
	void displayNodeHelper(TreeNode<NODETYPE>*) const;
	void postDisplayNodeHelper(TreeNode<NODETYPE>*) const;
	void inOrderDisplayHelper(TreeNode<NODETYPE>*) const;
	int heightHelper(TreeNode<NODETYPE>* ptr);
	int sizeHelper(TreeNode<NODETYPE>* ptr);
	int minHelper(TreeNode<NODETYPE>* ptr);
	int maxHelper(TreeNode<NODETYPE>* ptr);
public:
	Tree();
	//we are making a function insertNode accesible in main
	void insertNode(const NODETYPE&);
	void removeNode(const NODETYPE &);
	void displayNode() const;
	void postDisplayNode() const;
	void inOrderDisplayNode() const;
	void height();
	void size();
	void min();
	void max();
};
//constructer
template<typename NODETYPE>
Tree<NODETYPE>::Tree() { rootPtr = 0; }

template<typename NODETYPE>
void Tree<NODETYPE>::min() {
	std::cout << std::endl << "smallest value: " << minHelper(rootPtr) << std::endl;
}
template<typename NODETYPE>
int Tree<NODETYPE>::minHelper(TreeNode<NODETYPE>* ptr) {
	while (ptr->leftPtr != NULL) {
		ptr = ptr->leftPtr;
	}
	return(ptr->data);
}

template<typename NODETYPE>
void Tree<NODETYPE>::max() {
	std::cout << std::endl << "max value: " << maxHelper(rootPtr) << std::endl;
}
template<typename NODETYPE>
int Tree<NODETYPE>::maxHelper(TreeNode<NODETYPE>* ptr) {
	while (ptr->rightPtr != NULL) {
		ptr = ptr->rightPtr;
	}
	return(ptr->data);
}

template<typename NODETYPE>
void Tree<NODETYPE>::insertNode(const NODETYPE& value) {
	//private functions are functions that 
	insertNodeHelper(&rootPtr, value);
}

template<typename NODETYPE>
void Tree<NODETYPE>::insertNodeHelper(TreeNode<NODETYPE>** ptr, const NODETYPE& value) {
	//we first check if the value of ptr is null
	if (*ptr == 0) {
		//creating a new ptr object and setting it to the value of value
		*ptr = new TreeNode<NODETYPE>(value);
	}
	else {
		if (value < (*ptr)->data) {
			insertNodeHelper(&((*ptr)->leftPtr), value);
		}
		else {
			if (value > (*ptr)->data) {
				insertNodeHelper(&((*ptr)->rightPtr), value);
			}
			else {
				std::cout << value << " is a duplicate value" << std::endl;
			}
		}

	}

}
///remove node
template<typename NODETYPE>
void Tree<NODETYPE>::removeNode(const NODETYPE& value) {
	removeNodeHelper(&rootPtr, value);
}
template<typename NODETYPE>
int Tree<NODETYPE>::removeNodeHelper(TreeNode<NODETYPE>** ptr, const NODETYPE& value) {
	if (*ptr == 0) {
		//base case
		return(ptr->data);
	}
	//if the value we are searching for is smaller, then we know to progress to the left of the tree as it's smaller
	if (value < (*ptr)->data) {
		ptr->leftPtr = removeNodeHelper(ptr->leftPtr, value);
	}
	//if the value we are searching for is larger, then we know to progress to the right of the tree as it's bigger
	else if (value > (*ptr)->data) {
		ptr->leftPtr = removeNodeHelper(ptr->rightPtr, value);
	}
	//this is the hard part, if the value we are searching for is the root, then we have to start reassigning values in the tree
	else {
		// we first check if it has one or less nodes
		if (&(*ptr)->leftPtr == nullptr)
		{
			Tree <NODETYPE> temp = ptr->rightPtr;
			ptr = ptr->leftPtr;
			delete temp;							///LINES 118 and 124 are used to delete, but am getting errors there
		}
		else if (&(*ptr)->rightPtr == nullptr)
		{
			Tree <NODETYPE> temp = ptr->leftPtr;
			ptr = ptr->rightPtr;
			delete temp;
		}
		//else {
			int temp = maxHelper(rootPtr);
			ptr->data = temp;
			&ptr->rightPtr = removeNodeHelper(&((*ptr)->rightPtr), temp);
		//}
	}
	return (ptr->data);
}
///end of remove node
//this function is what starts outputting it at the start of the tree
template<typename NODETYPE>
void Tree<NODETYPE>::displayNode() const {
	std::cout << "pre order: " << std::endl;
	displayNodeHelper(rootPtr);

}
template<typename NODETYPE>
void Tree<NODETYPE>::postDisplayNode()const {
	std::cout << std::endl << "post order: " << std::endl;
	postDisplayNodeHelper(rootPtr);
}
template<typename NODETYPE>
void Tree<NODETYPE>::inOrderDisplayNode() const {
	std::cout << std::endl << "in order: " << std::endl;
	inOrderDisplayHelper(rootPtr);
}
///size function
template <typename NODETYPE>
void Tree<NODETYPE>::size() {
	std::cout << std::endl << "size of tree: " << sizeHelper(rootPtr) << std::endl;
}
template <typename NODETYPE>
int Tree<NODETYPE>::sizeHelper(TreeNode<NODETYPE>* ptr) {
	//first make sure there are values in binary tree, if there isn't we return 0
	if (ptr == nullptr) {
		return 0;
	}
	else {
		//each time it is called we want to just add one (basically the count of the times ran)
		return(sizeHelper(ptr->leftPtr) + 1 + sizeHelper(ptr->rightPtr));
	}
}
///end of size function

///height function
template <typename NODETYPE>
void Tree<NODETYPE>::height() {
	std::cout << std::endl << "height: " << heightHelper(rootPtr) << std::endl;
}
template <typename NODETYPE>
int Tree<NODETYPE>::heightHelper(TreeNode<NODETYPE>* ptr) {
	//first make sure there are values in binary tree, if there isn't we return 0
	if (ptr == nullptr) {
		return 0;
	}
	else {
		//since we are returnign data, we can create variables and set them equal to which one has won (done recursivly)
		int leftDepth = heightHelper(ptr->leftPtr);
		int rightDepth = heightHelper(ptr->rightPtr);

		// we are passing forward the side that has more nodes. It's almost like a tournament 
		if (leftDepth > rightDepth) {
			return(leftDepth + 1);
		}
		else {
			return(rightDepth + 1);
		}
	}
}
///end of height function

//we are recursivly outputting the values in the tree just like how we added them
//it's so we don't have to be saving data 
template<typename NODETYPE>
void Tree<NODETYPE>::displayNodeHelper(TreeNode<NODETYPE>* ptr) const {
	if (ptr != nullptr) {
		//ptr->data++;	//increments all data, (used for test)
		//if at the beginning (like this one), it is outputting from the start
		std::cout << ptr->data << " ";
		displayNodeHelper(ptr->leftPtr);
		//if the output is in the middle, it is outputting it in order
		displayNodeHelper(ptr->rightPtr);
		//if output is at end, it is outputting from the end
	}
}
template<typename NODETYPE>
void Tree<NODETYPE>::postDisplayNodeHelper(TreeNode<NODETYPE>* ptr) const {
	if (ptr != nullptr) {
		//if at the beginning , it is outputting from the start
		postDisplayNodeHelper(ptr->leftPtr);
		//if the output is in the middle, it is outputting it in order
		postDisplayNodeHelper(ptr->rightPtr);
		//if output is at end, it is outputting from the end(like this one)
		std::cout << ptr->data << " ";

	}
}
template<typename NODETYPE>
void Tree<NODETYPE>::inOrderDisplayHelper(TreeNode<NODETYPE>* ptr) const {
	if (ptr != nullptr) {
		inOrderDisplayHelper(ptr->leftPtr);
		std::cout << ptr->data << " ";
		inOrderDisplayHelper(ptr->rightPtr);
	}
}
#endif
#pragma once
