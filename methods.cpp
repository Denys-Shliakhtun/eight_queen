#include "pch.h"
#include "methods.h"

void stressTest()
{
	bool flag;
	ChessBoard* temp, * temp2;
	int k, l, d1, d2;
	//const int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	for (int i = 11111111; i < 88888888; i++)
	{
		flag = true;
		k = 10000000;
		while (k > 1 && flag)
		{
			d1 = i % (k * 10) / k;
			l = k / 10;
			while (l > 0 && flag)
			{
				d2 = i % (l * 10) / l;
				if (d1 == d2 || (d1 > 8 || d1 < 1) || (d2 > 8 || d2 < 1))
				{
					flag = false;
				}
				l /= 10;
			}
			k /= 10;
		}
		if (flag)
		{
			temp = new ChessBoard();
			for (int j = 0; j < 8; j++)
			{
				temp->insertQueen(i % (int)pow(10, j + 1) / (int)pow(10, j) - 1, j);
			}
			temp2 = BFS(temp);
			if (temp2 == NULL)
				temp2 = NULL;
			//displayResult(temp2);
			delete temp, temp2;
		}
	}
}

ChessBoard* LDFS(ChessBoard* main)
{
	if (!main->queenCheck())
		return new ChessBoard(main);
	std::stack<TreeNode*> stack;
	TreeNode* root = new TreeNode(new ChessBoard(main), 56);
	stack.push(root);
	TreeNode *temp, *temp2; 
	int counter = 0;
	bool flag = true;
	int lexNum;
	std::vector<ChessBoard*> chessBoardArr;
	while (flag)
	{
		temp = stack.top();
		
		chessBoardArr = temp->getNodeData()->boardBestArrGen();
		lexNum = rand() % chessBoardArr.size();
		temp2 = temp->insertNode(chessBoardArr[lexNum], lexNum);
		stack.push(temp2);
		if (!temp2->getNodeData()->queenCheck())
			flag = false;
		counter++;

		if(stack.size() > 1000000)
		{
			root->deleteTree();
			delete root;
			return NULL;
		}
	}
	ChessBoard* board = new ChessBoard(temp2->getNodeData());
	
	root->deleteTree();
	delete root;
	return board;
}

ChessBoard* BFS(ChessBoard* main)
{
	if (!main->queenCheck())
		return new ChessBoard(main);
	std::queue <TreeNode*> plan;
	TreeNode* temp = new TreeNode(new ChessBoard(main), 56);
	plan.push(temp);
	int counter = 1;
	bool flag = temp->getNodeData()->queenCheck();
	TreeNode* temp2 = temp;
	std::vector<ChessBoard*> chessBoardArr;
	while (flag)
	{
		temp = plan.front();
		plan.pop();
		chessBoardArr = temp->getNodeData()->boardBestArrGen();

		for (int i = 0; i < chessBoardArr.size() && flag; i++)
		{			
			temp2 = temp->insertNode(chessBoardArr[i], i);
			plan.push(temp2);
			if (!temp2->getNodeData()->queenCheck())				
				flag = false;			
			counter++;			
		}

		if (temp2 != temp)
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

ChessBoard* IDS(ChessBoard* main, int max_depth)
{
	if (!main->queenCheck())
		return new ChessBoard(main);
	TreeNode* head = new TreeNode(main, 56);
	TreeNode* temp;
	for (int i = 0; i <= max_depth; i++)
	{
		temp = DLS(head, i);
		if (temp != NULL)
		{
			temp->getNodeData()->fileOutput();
			ChessBoard* board = new ChessBoard(temp->getNodeData());
			head->deleteTree();
			//delete head;
			return board;
		}
		else
			head->deleteTree();
	}

	return NULL;
}

TreeNode* DLS(TreeNode* src, int limit)
{
	if (!src->getNodeData()->queenCheck())
		return src;

	// If reached the maximum depth, stop recursing.
	if (limit <= 0)	
		return NULL;
	
	// Recur for all the vertices adjacent to source vertex
	TreeNode* temp;
	TreeNode* temp2;
	
	std::vector<ChessBoard*> chessBoardArr = src->getNodeData()->boardBestArrGen();

	for (int i = 0; i < chessBoardArr.size(); i++)
	{
		temp = src->insertNode(chessBoardArr[i], i);
		temp2 = DLS(temp, limit - 1);
		if (temp2 != NULL)
			return temp2;
	}	

	return NULL;
}