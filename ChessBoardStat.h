#pragma once
#include "ChessBoard.h"

class ChessBoardStat : public ChessBoard
{
private:
	const int 
		count,	// кількість вершин дерева
		max,	// максимальна кількість вершин, що існували одночасно
		depth;	// висота дерева
public:
	// констурктор з параметрами
	ChessBoardStat(ChessBoard* prev, int parCount, int parMax, int parDepth) 
		: ChessBoard(prev), count(parCount), max(parMax), depth(parDepth) {};
	
	// виведення статистики у вікно повідомлення
	void messageBoxShow();

	// виведення дошки і таблиці у файл
	void fileOutput(std::ofstream& fileOut);
};