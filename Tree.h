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
	void deleteTree();
	~TreeNode();
};
