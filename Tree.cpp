#include "pch.h"
#include "Tree.h"

TreeNode::TreeNode(ChessBoard* param, int num)
{
	data = param;
	childNum = num;
	nodePointer = new TreeNode * [childNum];
	for (int i = 0; i < childNum; i++)
		nodePointer[i] = NULL;
}

TreeNode* TreeNode::insertNode(ChessBoard* param, int pos)
{
	nodePointer[pos] = new TreeNode(param, childNum); 
	return nodePointer[pos];
}

TreeNode** TreeNode::getNodePointer()
{
	return nodePointer;
}

ChessBoard* TreeNode::getNodeData() 
{ 
	return data; 
}

TreeNode::~TreeNode()
{
	delete data;
	delete[] nodePointer;
};