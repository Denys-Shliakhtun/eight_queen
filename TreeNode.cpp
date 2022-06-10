#include "pch.h"
#include "TreeNode.h"
#include <queue>
using namespace Local;

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

ChessBoard* TreeNode::getNodeData() 
{ 
	return data; 
}

int TreeNode::getChildNum()
{
	return childNum;
}

TreeNode* TreeNode::getCertainChild(int num)
{
	return nodePointer[num];
}

void TreeNode::deleteTreeBranch(TreeNode* node, int &counter)
{
	if (node == NULL)
		return;

	counter++;

	for (int i = 0; i < childNum; i++)
		deleteTreeBranch(node->getCertainChild(i), counter);	

	delete node;
}

int TreeNode::deleteTree()
{
	int counter = 0;
	for (int i = 0; i < childNum; i++)
	{
		deleteTreeBranch(nodePointer[i], counter);
		nodePointer[i] = NULL;
	}
	return counter;
}

TreeNode::~TreeNode()
{
	delete data;
	delete[childNum] nodePointer;
};