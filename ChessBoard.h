#pragma once
#include "const.h"
#include <fstream>

class ChessBoard
{
	//0 - empty
	//1 - queen
	unsigned char** board;
	void ChessBoardPointerDecl()
	{
		board = new unsigned char* [FIELD_SIZE];
		for (int i = 0; i < FIELD_SIZE; i++) board[i] = new unsigned  char[FIELD_SIZE];
	}
	void ChessBoardCopy(ChessBoard* prev)
	{
		for (int i = 0; i < FIELD_SIZE; i++)
		{

			for (int j = 0; j < FIELD_SIZE; j++)
			{
				board[i][j] = prev->board[i][j];
			}
		}
	}
public:	
	ChessBoard() { 
		ChessBoardPointerDecl();
		set();
	};

	ChessBoard(ChessBoard* prev) {
		ChessBoardPointerDecl();
		ChessBoardCopy(prev);
	}

	ChessBoard(ChessBoard* prev, int pos1, int pos2 = -1) {
		ChessBoardPointerDecl();
		ChessBoardCopy(prev);

		if (pos2 == -1)
			pos2 = (pos1 + 1) % FIELD_SIZE;

		int temp;
		for (int i = 0; i < FIELD_SIZE; i++)
		{
			temp = board[i][pos1];
			board[i][pos1] = board[i][pos2];
			board[i][pos2] = temp;
		}
	}

	void set() {
		for (int i = 0; i < FIELD_SIZE; i++)
		{
			for (int j = 0; j < FIELD_SIZE; j++)
			{
				board[i][j] = 0;
				if (i == j)
					board[i][j] = 1;
			}
		}
	}

	//true if queen hits another queen
	bool queenCheck()
	{
		bool flag = false;
		for (int i = 0; i < FIELD_SIZE && !flag; i++)		
			for (int j = 0; j < FIELD_SIZE && !flag; j++)			
				if (board[i][j] == 1 && !flag)
					flag = queenCheckDiagonal(i, j);
		return flag;
	}

	bool queenCheckStraight(int a, int b)
	{
		for (int i = 1; i < FIELD_SIZE; i++)
		{
			if (board[(a + i) % FIELD_SIZE][b] == 1)
				return true;
			if (board[a][(b + i) % FIELD_SIZE] == 1)
				return true;
		}
		return false;
	}
	
	bool queenCheckDiagonal(int a, int b)
	{
		int tempa = a, tempb = b;
		while (tempa > 0 && tempb > 0)
		{
			tempa--; tempb--;
		}
		while (tempa < FIELD_SIZE && tempb < FIELD_SIZE)
		{
			if (!(tempa == a && tempb == b) && board[tempa][tempb] == 1)
				return true;
			tempa++;
			tempb++;
		}

		tempa = a, tempb = b;
		while (tempa > 0 && tempb < FIELD_SIZE - 1)
		{
			tempa--; tempb++;
		}
		while (tempa < FIELD_SIZE && tempb >= 0 )
		{
			if (!(tempa == a && tempb == b) && board[tempa][tempb] == 1)
				return true;
			tempa++;
			tempb--;
		}

		return false;
	}

	void fileOutout()
	{
		std::ofstream fileOut("output.txt");
		for (int i = 0; i < FIELD_SIZE; i++)
		{
			for (int j = 0; j < FIELD_SIZE; j++)
			{
				fileOut << (board[i][j] == 0 ? '*' : 'q') << ' ';
			}
			fileOut << std::endl;
		}
		fileOut.close();
	}

	~ChessBoard()
	{
		for (int i = 0; i < FIELD_SIZE; i++) 
		{
			delete[FIELD_SIZE] board[i];
		}
		delete[FIELD_SIZE] board;
	}
};