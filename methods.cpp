#include "pch.h"
#include "methods.h"
//#include "Form1.h" //for output of every created board

using namespace Local;

ChessBoardStat* LDFS(ChessBoard* main)
{
	//checking whether parameter is the solution of task
	if (!main->queenCheck())
		return new ChessBoardStat(main, 1, 1, 0);

	//variables for LDFS algorithm
	std::stack<TreeNode*> stack;
	TreeNode* root = new TreeNode(new ChessBoard(main), 56);
	stack.push(root);
	TreeNode *temp, *temp2; 	
	bool flag = true;
	int lexNum;
	std::vector<ChessBoard*> chessBoardArr;
	
	//LDFS algorithm
	while (flag)
	{
		temp = stack.top();
		
		chessBoardArr = temp->getNodeData()->boardBestArrGen();
		lexNum = rand() % chessBoardArr.size();
		temp2 = temp->insertNode(chessBoardArr[lexNum], lexNum);
		stack.push(temp2);
		if (!temp2->getNodeData()->queenCheck())
			flag = false;
		for (int i = 0; i < chessBoardArr.size(); i++)
			if (i != lexNum)
				delete chessBoardArr[i];
		//CppCLRWinformsProject::Form1::FormPointer->displayResult(chessBoardArr[lexNum]);
	}

	//result
	ChessBoard* board = new ChessBoard(temp2->getNodeData());
	int counter = root->deleteTree() + 1;
	delete root;
	ChessBoardStat* result = new ChessBoardStat(board, counter, counter, counter - 1);
	delete board;
	
	return result;
}

ChessBoardStat* BFS(ChessBoard* main)
{
	//checking whether parameter is the solution of task
	if (!main->queenCheck())
		return new ChessBoardStat(main, 1, 1, 0);
	
	//variables for statistics
	int counter = 1;
	int maxCount = 1;

	//variables for BFS algorithm
	std::vector<int> depthCounter;
	std::queue <TreeNode*> plan;
	TreeNode* temp = new TreeNode(new ChessBoard(main), 56);
	plan.push(temp);
	bool flag = temp->getNodeData()->queenCheck();
	TreeNode* temp2 = temp;
	std::vector<ChessBoard*> chessBoardArr;

	while (flag)
	{
		//BFS algorithm
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
			//CppCLRWinformsProject::Form1::FormPointer->displayResult(chessBoardArr[i]);
		}

		//counting max count of existing nodes at the same time
		if (maxCount < plan.size() + 1)
			maxCount = plan.size() + 1;

		//counting the depth of the tree
		depthCounter.push_back(chessBoardArr.size());

		//deleting nodes that will not be used anymore
		if (temp2 != temp)
			delete temp;
	}
	
	//deleting all the remaining tree nodes
	while (plan.size() > 1)
	{
		temp = plan.front();
		plan.pop();
		delete temp;
	}

	//calculating the depth of the tree
	int pos = 1;
	int tempCount = depthCounter[0];
	int tempSum = 0;
	int depth = 1;
	while (pos < depthCounter.size())
	{
		tempSum = 0;
		for (int i = pos; i < pos + tempCount && pos + tempCount < depthCounter.size(); i++)
		{
			tempSum += depthCounter[i];
		}
		pos += tempCount;
		tempCount = tempSum;
		
		depth++;
	}
	
	ChessBoardStat* result = new ChessBoardStat(temp2->getNodeData(), counter, maxCount, depth);
	delete temp2;
	return result;
}

ChessBoardStat* IDS(ChessBoard* main, int max_depth)
{
	//checking whether parameter is the solution of task
	if (!main->queenCheck())
		return new ChessBoardStat(main, 1, 1, 0);

	int lastCount = 0, prelastCount = 0, counter = 0; //variables for statistics

	//IDS algorithm
	TreeNode* head = new TreeNode(main, 56);
	TreeNode* temp;	
	ChessBoardStat* result = NULL;
	for (int i = 0; i <= max_depth && result == NULL; i++)
	{
		temp = DLS(head, i);
		if (temp != NULL)
		{
			ChessBoard* board = new ChessBoard(temp->getNodeData());

			//statistics and deleting tree
			lastCount = head->deleteTree() + 1;
			counter += lastCount;
			delete head;
			result = new ChessBoardStat(board, counter, lastCount > prelastCount ? lastCount : prelastCount, i);
			delete board;
		}
		else
		{
			//deleting tree and counting statistics
			prelastCount = head->deleteTree();
			counter += prelastCount++;
		}
	}

	return result;
}

TreeNode* DLS(TreeNode* src, int limit)
{
	//returns src if it is the solution of task
	if (!src->getNodeData()->queenCheck())
		return src;

	//stopping recursion
	if (limit <= 0)	
		return NULL;
	
	//regular algorithm
	TreeNode* temp;
	TreeNode* temp2;	
	std::vector<ChessBoard*> chessBoardArr = src->getNodeData()->boardBestArrGen();

	for (int i = 0; i < chessBoardArr.size(); i++)
	{
		temp = src->insertNode(chessBoardArr[i], i);
		temp2 = DLS(temp, limit - 1);
		if (temp2 != NULL)
			return temp2;
		//CppCLRWinformsProject::Form1::FormPointer->displayResult(chessBoardArr[i]);
	}	

	//if the solution wasn't found
	return NULL;
}