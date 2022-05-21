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

void TreeNode::deleteTree()
{
	std::queue <TreeNode*> plan;
	TreeNode* temp;
	for (int i = 0; i < childNum; i++)
	{
		temp = nodePointer[i];
		if (temp!=NULL)
			plan.push(temp);
	}
	TreeNode* temp2;
	while (plan.size()>0)
	{
		temp = plan.front();
		plan.pop();
		for (int j = 0; j < temp->getChildNum(); j++)
		{
			temp2 = temp->getCertainChild(j);
			if(temp2 != NULL)
				plan.push(temp2);
		}
		if (temp!=NULL)
			delete temp;
	}
}

TreeNode::~TreeNode()
{
	delete data;
	delete[childNum] nodePointer;
};