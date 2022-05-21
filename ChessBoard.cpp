#include "pch.h"
#include "ChessBoard.h"

const int ChessBoard::FIELD_SIZE = 8;

void ChessBoard::pointerDecl()
{
	board = new unsigned char* [FIELD_SIZE];
	for (int i = 0; i < FIELD_SIZE; i++) board[i] = new unsigned  char[FIELD_SIZE];
}

void ChessBoard::setBoard(ChessBoard* prev)
{
	for (int i = 0; i < FIELD_SIZE; i++)
		for (int j = 0; j < FIELD_SIZE; j++)
			board[i][j] = prev->board[i][j];
}

ChessBoard::ChessBoard() {
	pointerDecl();
	setValue();
}

ChessBoard::ChessBoard(ChessBoard* prev) {
	pointerDecl();
	setBoard(prev);
}

ChessBoard::ChessBoard(ChessBoard* prev, int pos1, int pos2)
{
	pointerDecl();
	setBoard(prev);
	pos1 %= FIELD_SIZE;

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

void ChessBoard::setValue() {
	for (int i = 0; i < FIELD_SIZE; i++)
	{
		for (int j = 0; j < FIELD_SIZE; j++)
		{
			board[i][j] = 0;
		}
	}
}

bool ChessBoard::queenCheck()
{
	bool flag = false;
	for (int i = 0; i < FIELD_SIZE && !flag; i++)
		for (int j = 0; j < FIELD_SIZE && !flag; j++)
			if (board[i][j] == 1 && !flag)
				flag = queenCheckDiagonal(i, j);
	return flag;
}

bool ChessBoard::queenCheckStraight(int a, int b)
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

bool ChessBoard::queenCheckDiagonal(int a, int b)
{
	int tempa = a, tempb = b;
	while (tempa > 0 && tempb > 0)
	{
		tempa--; tempb--;
		if (board[tempa][tempb] == 1)
			return true;
	}

	tempa = a, tempb = b;
	while (tempa < FIELD_SIZE - 1 && tempb < FIELD_SIZE - 1)
	{
		tempa++; tempb++;
		if (board[tempa][tempb] == 1)
			return true;
	}

	tempa = a, tempb = b;
	while (tempa > 0 && tempb < FIELD_SIZE - 1)
	{
		tempa--; tempb++;
		if (board[tempa][tempb] == 1)
			return true;
	}

	tempa = a, tempb = b;
	while (tempa < FIELD_SIZE - 1 && tempb > 0)
	{
		tempa++; tempb--;
		if (board[tempa][tempb] == 1)
			return true;
	}

	return false;
}

void ChessBoard::fileOutput()
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

void ChessBoard::insertQueen(int x, int y)
{
	board[x%FIELD_SIZE][y % FIELD_SIZE] = 1;
}

void ChessBoard::removeQueen(int x, int y)
{
	board[x % FIELD_SIZE][y % FIELD_SIZE] = 0;
}

std::vector<std::vector<int>> ChessBoard::getQueenPos()
{
	std::vector<std::vector<int>> result;
	for (int i = 0; i < FIELD_SIZE; i++)
	{
		for (int j = 0; j < FIELD_SIZE; j++)
		{
			if(board[i][j]==1)
				result.push_back({ i, j });
		}
	}
	return result;
}

//true if can calculate
bool ChessBoard::queenFirstCheck()
{
	int counter = 0;
	for (int i = 0; i < FIELD_SIZE; i++)
		for (int j = 0; j < FIELD_SIZE; j++)
			if (board[i][j] == 1)
			{
				counter++;
				if (queenCheckStraight(i, j))
					return false;
			}
	return counter == FIELD_SIZE;
}

ChessBoard::~ChessBoard()
{
	for (int i = 0; i < FIELD_SIZE; i++)
	{
		delete[FIELD_SIZE] board[i];
	}
	delete[FIELD_SIZE] board;
}