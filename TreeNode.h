#ifndef TreeNode_h
#define TreeNode_h

//forward decleration so we can make it a friend of the class
template<typename NODETYPE>
class Tree;

template<typename NODETYPE>
class TreeNode {
	friend class Tree<NODETYPE>;
private:
	TreeNode* leftPtr;
	NODETYPE data;
	TreeNode* rightPtr;
public:
	TreeNode(const NODETYPE& d) {
		leftPtr = 0;
		rightPtr = 0;
		data = d;
	}
	NODETYPE getData() const {
		return data;
	}

};

#endif
#pragma once
