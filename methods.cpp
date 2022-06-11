#include "pch.h"
#include "methods.h"
//#include "Form1.h" //для виведення кожної проміжкової дошки

using namespace Local;

ChessBoardStat* LDFS(ChessBoard* main)
{
	// перевірка, чи параметр є розв'язком задачі
	if (!main->queenCheck())
		return new ChessBoardStat(main, 1, 1, 0);

	// змінні для LDFS алгоритму
	std::stack<TreeNode*> stack;
	TreeNode* root = new TreeNode(new ChessBoard(main), pow(ChessBoard::FIELD_SIZE, 2) - ChessBoard::FIELD_SIZE);
	stack.push(root);
	TreeNode *temp, *temp2; 	
	bool flag = true;
	int lexNum;
	std::vector<ChessBoard*> chessBoardArr;
	
	// LDFS алгоритм
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

	// результат
	ChessBoard* board = new ChessBoard(temp2->getNodeData());
	int counter = root->deleteTree() + 1;
	delete root;
	ChessBoardStat* result = new ChessBoardStat(board, counter, counter, counter - 1);
	delete board;
	
	return result;
}

ChessBoardStat* BFS(ChessBoard* main)
{
	// перевірка, чи параметр є розв'язком задачі
	if (!main->queenCheck())
		return new ChessBoardStat(main, 1, 1, 0);
	
	//v змінні для статистики
	int counter = 1;
	int maxCount = 1;

	// змінні для BFS алгоритму
	std::vector<int> depthCounter;
	std::queue <TreeNode*> plan;
	TreeNode* temp = new TreeNode(new ChessBoard(main), pow(ChessBoard::FIELD_SIZE, 2) - ChessBoard::FIELD_SIZE);
	plan.push(temp);
	bool flag = temp->getNodeData()->queenCheck();
	TreeNode* temp2 = temp;
	std::vector<ChessBoard*> chessBoardArr;

	while (flag)
	{
		//BFS алгоритм
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

		// визначення найбільшої кількості вершин, що існували в один момент
		if (maxCount < plan.size() + 1)
			maxCount = plan.size() + 1;

		// вектор для подальших обрахунків висоти дерева
		depthCounter.push_back(chessBoardArr.size());

		// видалення непотрібних вершин
		if (temp2 != temp)
			delete temp;
	}
	
	// видалення всіх вершин дерева, що залишилися
	while (plan.size() > 1)
	{
		temp = plan.front();
		plan.pop();
		delete temp;
	}

	// обчислення висоти дерева
	int pos = 1;
	int tempCount = depthCounter[0];
	int tempSum = 0;
	int depth = 1;
	while (pos < depthCounter.size())
	{
		tempSum = 0;
		for (int i = pos; i < pos + tempCount && pos + tempCount < depthCounter.size(); i++)		
			tempSum += depthCounter[i];		
		pos += tempCount;
		tempCount = tempSum;		
		depth++;
	}
	
	// результат
	ChessBoardStat* result = new ChessBoardStat(temp2->getNodeData(), counter, maxCount, depth);
	delete temp2;
	return result;
}

ChessBoardStat* IDS(ChessBoard* main, int max_depth)
{
	// перевірка, чи параметр є розв'язком задачі
	if (!main->queenCheck())
		return new ChessBoardStat(main, 1, 1, 0);

	int lastCount = 0, prelastCount = 0, counter = 0; //змінні для статистики

	//IDS алгоритм
	TreeNode* head = new TreeNode(new ChessBoard(main), pow(ChessBoard::FIELD_SIZE, 2) - ChessBoard::FIELD_SIZE);
	TreeNode* temp;	
	ChessBoardStat* result = NULL;
	for (int i = 0; i <= max_depth && result == NULL; i++)
	{
		temp = DLS(head, i);
		if (temp != NULL)
		{
			ChessBoard* board = new ChessBoard(temp->getNodeData());

			// статистика і видалення дерева
			lastCount = head->deleteTree() + 1;
			counter += lastCount;
			delete head;
			result = new ChessBoardStat(board, counter, lastCount > prelastCount ? lastCount : prelastCount, i);
			delete board;
		}
		else
		{
			// видалення дерева і обчислення статистики
			prelastCount = head->deleteTree();
			counter += prelastCount++;
		}
	}

	// результат
	return result;
}

TreeNode* DLS(TreeNode* src, int limit)
{
	// повернення src, якщо він є результатом задачі
	if (!src->getNodeData()->queenCheck())
		return src;

	// зупинка рекурсії
	if (limit <= 0)	
		return NULL;
	
	// подальший алгоритм заглиблення
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

	// якщо розв'язок не знайдено
	return NULL;
}