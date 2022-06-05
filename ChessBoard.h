#pragma once
#include <fstream>
#include <vector>

class ChessBoard
{
	// 0 - empty
	//>0 - queen

	unsigned char** board;
	void pointerDecl();
	void setBoard(ChessBoard* prev);
	void setEmptyBoard(); 
public:	
	static const int FIELD_SIZE;
	
	ChessBoard();

	ChessBoard(ChessBoard* prev);

	ChessBoard(ChessBoard* prev, int pos1, int pos2 = -1, int orientation = 1);
		
	//true if board can be processed
	bool queenFirstCheck();

	//true if queen hits another queen
	bool queenCheck();

	//true if queen hits another queen
	bool queenCheckStraight(int a, int b);
	
	//true if queen hits another queen
	bool queenCheckDiagonal(int a, int b);

	std::vector<std::vector<int>> ChessBoard::getQueenPos();	

	void insertQueen(int x, int y);

	void removeQueen(int x, int y);	

	int getQueenHitNumber();

	std::vector<ChessBoard*> boardBestArrGen();

	void fileOutput(std::ofstream&);

	~ChessBoard();
};