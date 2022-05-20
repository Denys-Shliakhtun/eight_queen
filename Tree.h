#pragma once
#include "const.h"
#include "ChessBoard.h"

class TreeNode
{
	TreeNode** nodePointer;
	ChessBoard* data;
	int childNum;
public:	
	TreeNode(ChessBoard*, int);
	TreeNode* insertNode(ChessBoard*, int); 
	TreeNode** getNodePointer();
	ChessBoard* getNodeData();
	~TreeNode();
};
