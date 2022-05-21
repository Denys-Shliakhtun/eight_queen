#pragma once
#include <fstream>
#include <vector>

class ChessBoard
{
	//0 - empty
	//1 - queen

	unsigned char** board;
	void pointerDecl();
	void setBoard(ChessBoard* prev);
public:	
	static const int FIELD_SIZE;
	ChessBoard();

	ChessBoard(ChessBoard* prev);

	ChessBoard(ChessBoard* prev, int pos1, int pos2 = -1);

	void setValue();

	bool queenFirstCheck();

	//true if queen hits another queen
	bool queenCheck();

	bool queenCheckStraight(int a, int b);
	
	bool queenCheckDiagonal(int a, int b);

	std::vector<std::vector<int>> ChessBoard::getQueenPos();

	void insertQueen(int x, int y);

	void removeQueen(int x, int y);

	void fileOutput();

	~ChessBoard();
};