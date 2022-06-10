#pragma once
#include "ChessBoard.h"

class ChessBoardStat : public ChessBoard
{
private:
	const int 
		count,	//number of nodes
		max,	//max number of nodes existing at the same time
		depth;	//the height of the tree
public:
	ChessBoardStat(ChessBoard* prev, int parCount, int parMax, int parDepth) 
		: ChessBoard(prev), count(parCount), max(parMax), depth(parDepth) {};
	
	void messageBoxShow();

	void fileOutput(std::ofstream& fileOut);
};