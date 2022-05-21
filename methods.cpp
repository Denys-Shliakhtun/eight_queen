#include "pch.h"
#include "methods.h"

ChessBoard* LDFS(ChessBoard* main)
{
	return main;
}

ChessBoard* BFS(ChessBoard* main)
{
	std::queue <TreeNode*> plan;
	TreeNode* temp = new TreeNode(new ChessBoard(main));
	plan.push(temp);
	int counter = 1;
	bool flag = temp->getNodeData()->queenCheck();
	TreeNode* temp2 = temp;
	ChessBoard* tempboard;
	int i = 0;
	while (flag)
	{
		temp = plan.front();
		plan.pop();
		
		for (int j = 0; j < 2 && flag; j++)
		{
			tempboard = new ChessBoard(temp->getNodeData(), j == 0 ? i 
				: ChessBoard::FIELD_SIZE - i - 1);
			temp2 = temp->insertNode(tempboard, j);
			plan.push(temp2);
			if (!temp2->getNodeData()->queenCheck())
				flag = false;
			counter++;
		}
		
		delete temp;
		i < ChessBoard::FIELD_SIZE - 1 ? i++ : i = 0;
	}
	while (plan.size()>1)
	{
		temp = plan.front();
		plan.pop();
		delete temp;
	}
	temp2->getNodeData()->fileOutput();
	return temp2->getNodeData();
}

/*
ChessBoard* BFS_nonBinaryTree(ChessBoard* main)
{
	std::queue <TreeNode*> plan;
	TreeNode* temp = new TreeNode(new ChessBoard(temp->getNodeData()), ChessBoard::FIELD_SIZE);
	plan.push(temp);
	int counter = 1;
	bool flag = temp->getNodeData()->queenCheck();
	TreeNode* temp2 = temp;

	while (flag)
	{
		temp = plan.front();
		plan.pop();
		for (int i = 0; i < ChessBoard::FIELD_SIZE && flag; i++)
		{
			temp2 = temp->insertNode(new ChessBoard(temp->getNodeData(), i), i);
			plan.push(temp2);
			if (!temp2->getNodeData()->queenCheck())
				flag = false;
			counter++;
		}
		delete temp;
	}
	while (plan.size() > 1)
	{
		temp = plan.front();
		plan.pop();
		delete temp;
	}
	temp2->getNodeData()->fileOutput();
	return temp2->getNodeData();
}
*/

ChessBoard* IDS(ChessBoard* main, int max_depth)
{
	TreeNode* head = new TreeNode(main);
	TreeNode* temp;
	for (int i = 0; i <= max_depth; i++)
	{
		temp = DLS(head, i);
		if (temp != NULL)
		{
			temp->getNodeData()->fileOutput();
			ChessBoard* board = new ChessBoard(temp->getNodeData());
			head->deleteTree();
			delete head;
			return board;
		}
		head->deleteTree();
	}

	return NULL;
}

TreeNode* DLS(TreeNode* src, int limit, int pos)
{
	if (!src->getNodeData()->queenCheck())
		return src;

	// If reached the maximum depth, stop recursing.
	if (limit <= 0)
	{
		//delete src;
		return NULL;
	}

	// Recur for all the vertices adjacent to source vertex
	
	int i = 0;
	for (int i = 0; i < 2; i++)
	{
		TreeNode* temp = src->insertNode(new ChessBoard(src->getNodeData(), i == 0 ? pos : ChessBoard::FIELD_SIZE - 1 - pos % ChessBoard::FIELD_SIZE), i);
		TreeNode* temp2 = DLS(temp, limit - 1, pos + 1);
		if (temp2 != NULL)
			return temp2;
	}

	//delete src;
	return NULL;
}