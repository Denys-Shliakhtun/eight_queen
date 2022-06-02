#include "pch.h"
#include "ChessBoard.h"
#include <algorithm>  

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

ChessBoard::ChessBoard(ChessBoard* prev, int pos1, int pos2, int orientation)
{
	pointerDecl();
	setBoard(prev);
	pos1 %= FIELD_SIZE;

	if (pos2 == -1)
		pos2 = (pos1 + 1) % FIELD_SIZE;
	else
		pos2 %= FIELD_SIZE;

	int temp;
	switch (orientation)
	{
		case 1: //columns
			for (int i = 0; i < FIELD_SIZE; i++)
			{
				temp = board[i][pos1];
				board[i][pos1] = board[i][pos2];
				board[i][pos2] = temp;
			}
			break;
		case 2: //rows
			for (int i = 0; i < FIELD_SIZE; i++)
			{
				temp = board[pos1][i];
				board[pos1][i] = board[pos2][i];
				board[pos2][i] = temp;
			}
	}
}

void ChessBoard::setValue() {
	for (int i = 0; i < FIELD_SIZE; i++)	
		for (int j = 0; j < FIELD_SIZE; j++)		
			board[i][j] = 0;	
}

bool ChessBoard::queenCheck()
{
	bool flag = false;
	for (int i = 0; i < FIELD_SIZE && !flag; i++)
		for (int j = 0; j < FIELD_SIZE && !flag; j++)
			if (board[i][j] != 0 && !flag)
				flag = queenCheckDiagonal(i, j);
	return flag;
}

bool ChessBoard::queenCheckStraight(int a, int b)
{
	for (int i = 1; i < FIELD_SIZE; i++)
	{
		if (board[(a + i) % FIELD_SIZE][b] != 0)
			return true;
		if (board[a][(b + i) % FIELD_SIZE] != 0)
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
		if (board[tempa][tempb] != 0)
			return true;
	}

	tempa = a, tempb = b;
	while (tempa < FIELD_SIZE - 1 && tempb < FIELD_SIZE - 1)
	{
		tempa++; tempb++;
		if (board[tempa][tempb] != 0)
			return true;
	}

	tempa = a, tempb = b;
	while (tempa > 0 && tempb < FIELD_SIZE - 1)
	{
		tempa--; tempb++;
		if (board[tempa][tempb] != 0)
			return true;
	}

	tempa = a, tempb = b;
	while (tempa < FIELD_SIZE - 1 && tempb > 0)
	{
		tempa++; tempb--;
		if (board[tempa][tempb] != 0)
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
	unsigned char temp = 0;
	for (int i = 0; i < FIELD_SIZE; i++)
		for (int j = 0; j < FIELD_SIZE; j++)
			if (temp < board[i][j])
				temp = board[i][j];
	if(board[x % FIELD_SIZE][y % FIELD_SIZE] == 0)
		board[x % FIELD_SIZE][y % FIELD_SIZE] = temp + 1;
}

void ChessBoard::removeQueen(int x, int y)
{
	unsigned char temp = board[x % FIELD_SIZE][y % FIELD_SIZE];
	if (temp != 0)
		for (int i = 0; i < FIELD_SIZE; i++)
			for (int j = 0; j < FIELD_SIZE; j++)
				if (temp < board[i][j])
					board[i][j]--;
	board[x % FIELD_SIZE][y % FIELD_SIZE] = 0;
}

bool sortVec(std::vector<int> v1, std::vector<int> v2)
{
	return (v1[2] > v2[2]);
}

std::vector<std::vector<int>> ChessBoard::getQueenPos()
{
	std::vector<std::vector<int>> result;
	for (int i = 0; i < FIELD_SIZE; i++)
	{
		for (int j = 0; j < FIELD_SIZE; j++)
		{
			if(board[i][j]!=0)
				result.push_back({ i, j, board[i][j] });
		}
	}
	sort(result.begin(), result.end(), sortVec);
	return result;
}

int ChessBoard::getQueenHitNumber()
{
	int count = 0;
	for (int i = 0; i < FIELD_SIZE; i++)
	{
		for (int j = 0; j < FIELD_SIZE; j++)
		{
			if (board[i][j] != 0)
				if (queenCheckDiagonal(i, j))
					count++;
		}
	}
	return count;
}

//true if can calculate
bool ChessBoard::queenFirstCheck()
{
	int counter = 0;
	for (int i = 0; i < FIELD_SIZE; i++)
		for (int j = 0; j < FIELD_SIZE; j++)
			if (board[i][j] != 0)
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

std::vector<ChessBoard*> ChessBoard::boardBestArrGen()
{
	int queenHit = FIELD_SIZE;
	ChessBoard** tempboard = new ChessBoard * [56];
	bool flag = true;
	int pos = 0;

	for (int orientation = 1; orientation <= 2 && flag; orientation++)
		for (int j = 0; j < ChessBoard::FIELD_SIZE - 1 && flag; j++)
			for (int k = j + 1; k < ChessBoard::FIELD_SIZE && flag; k++)
			{
				tempboard[pos] = new ChessBoard(this, j, k, orientation);
				if (queenHit >= tempboard[pos]->getQueenHitNumber())
					queenHit = tempboard[pos]->getQueenHitNumber();
				pos++;
			}

	std::vector<ChessBoard*> result;
	for (int i = 0; i < 56 && flag; i++)
	{
		if (tempboard[i]->getQueenHitNumber() == queenHit)
			result.push_back(tempboard[i]);
		else
			delete tempboard[i];
	}

	delete[] tempboard;
	return result;
}