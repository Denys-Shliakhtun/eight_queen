#include "pch.h"
#include "Tree.h"
#include "queue"

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

int TreeNode::getChildNum()
{
	return childNum;
}

TreeNode* TreeNode::getCertainChild(int num)
{
	return nodePointer[num];
}

void TreeNode::deleteCertainChild(int num)
{
	delete nodePointer[num];
	nodePointer[num] = NULL;
}

void TreeNode::deleteTreeBranch(TreeNode* node)
{
	if (node == NULL)
		return;

	for (int i = 0; i < childNum; i++)
		deleteTreeBranch(node->getCertainChild(i));	

	delete node;
}

void TreeNode::deleteTree()
{
	for (int i = 0; i < childNum; i++)
	{
		deleteTreeBranch(nodePointer[i]);
		nodePointer[i] = NULL;
	}
}

TreeNode::~TreeNode()
{
	delete data;
	delete[childNum] nodePointer;
};