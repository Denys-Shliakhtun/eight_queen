#pragma once
#include "ChessBoard.h"
namespace Local {
	class TreeNode
	{
		TreeNode** nodePointer;
		ChessBoard* data;
		int childNum;
		void deleteTreeBranch(TreeNode* node);
	public:	
		TreeNode(ChessBoard*, int num = 2);
		TreeNode* insertNode(ChessBoard*, int); 
		ChessBoard* getNodeData();
		int getChildNum();
		TreeNode* getCertainChild(int);
		void deleteTree();
		~TreeNode();
	};
}
