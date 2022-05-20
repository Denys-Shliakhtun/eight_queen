#include "pch.h"
#include "methods.h"

ChessBoard* LDFS(ChessBoard* main)
{
	return main;
}

ChessBoard* BFS(ChessBoard* main)
{
	std::queue <TreeNode*> plan;
	TreeNode* temp = new TreeNode(new ChessBoard(main), 2);
	plan.push(temp);
	int counter = 1;
	bool flag = temp->getNodeData()->queenCheck();
	TreeNode* temp2 = temp;
	int i = 0;
	while (flag)
	{
		temp = plan.front();
		plan.pop();
		
		for (int j = 0; j < 2 && flag; j++)
		{
			temp2 = temp->insertNode(new ChessBoard(temp->getNodeData(), j == 0 ? i : (FIELD_SIZE - i) % FIELD_SIZE), j);
			plan.push(temp2);
			if (!temp2->getNodeData()->queenCheck())
				flag = false;
			counter++;
		}
		
		delete temp;
		i < FIELD_SIZE - 1 ? i++ : i = 0;
	}
	while (plan.size()>1)
	{
		temp = plan.front();
		plan.pop();
		delete temp;
	}
	temp2->getNodeData()->fileOutout();
	return temp2->getNodeData();
}

/*
ChessBoard* BFS_nonBinaryTree(ChessBoard* main)
{
	std::queue <TreeNode*> plan;
	TreeNode* temp = new TreeNode(new ChessBoard(temp->getNodeData()), FIELD_SIZE);
	plan.push(temp);
	int counter = 1;
	bool flag = temp->getNodeData()->queenCheck();
	TreeNode* temp2 = temp;

	while (flag)
	{
		temp = plan.front();
		plan.pop();
		for (int i = 0; i < FIELD_SIZE && flag; i++)
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
	temp2->getNodeData()->fileOutout();
	return temp2->getNodeData();
}
*/

ChessBoard* IDS(ChessBoard* main)
{
	return main;
}