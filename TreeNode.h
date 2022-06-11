#pragma once
#include "ChessBoard.h"
namespace Local {
	class TreeNode
	{
		// масив покажчиків на вершини-нащадки
		TreeNode** nodePointer;

		// дані вершини - шахова дошка
		ChessBoard* data;

		// кількість нащадків
		int childNum;

		// видалення гілки дерева рекурсивною функцією
		void deleteTreeBranch(TreeNode*, int&);
	public:	
		// конструктор, покажчик на дошку та кількість нащадків
		TreeNode(ChessBoard*, int num = 2);

		// вставлення вершини-нащадка на задану позицію
		TreeNode* insertNode(ChessBoard*, int); 

		// геттер покажчика на шахову дошку
		ChessBoard* getNodeData();

		// геттер кількості нащадків
		int getChildNum();

		// геттер нащадка певної позиції
		TreeNode* getCertainChild(int);

		// видалення усіх нащадків вершини
		int deleteTree();

		// деструктор
		~TreeNode();
	};
}
