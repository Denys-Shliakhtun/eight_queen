#pragma once
#include "ChessBoard.h"

class TreeNode
{
	TreeNode** nodePointer;
	ChessBoard* data;
	int childNum;
public:	
	TreeNode(ChessBoard*, int num = 2);
	TreeNode* insertNode(ChessBoard*, int); 
	TreeNode** getNodePointer();
	ChessBoard* getNodeData();
	int getChildNum();
	TreeNode* getCertainChild(int);
	void deleteCertainChild(int);
	void TreeNode::deleteTreeBranch(TreeNode* node);
	void deleteTree();
	~TreeNode();
};
