#pragma once
#include <fstream>
#include <vector>

class ChessBoard
{
	// оголошення динамічної матриці дошки
	void pointerDecl(); 
	
	// присвоїти значення іншої дошки
	void setBoard(ChessBoard* prev); 
	
	// встановити пусту дошку
	void setEmptyBoard();  
protected:
	// матриця шахової дошки
	// 0	- пуста клітинка
	// >0	- номер ферзя на дошці
	unsigned char** board;
public:	
	// розмір шахового поля
	static const int FIELD_SIZE;	
	
	//----------конструктори-----------

	// створення пустої дошки
	ChessBoard();

	// конструктор копіювання
	ChessBoard(ChessBoard* prev);

	// конструктор з перестановкою стовпчиків або колонок попередньої дошки
	ChessBoard(ChessBoard*, int, int pos2 = -1, int orientation = 1);
		
	//----------конструктори-----------

	// попередня перевірка дошки для обробки її методами
	// перевірка лише по прямим
	// true, якщо дошка підлягає обробці
	bool queenFirstCheck();

	// перевірка під час виконання методів
	// перевірка лише по діагоналям
	// true, якщо ферзь може забрати іншого ферзя
	bool queenCheck();

	// перевірка, чи заданий ферзь може атакувати іншу фігуру по прямій
	// true, якщо ферзь може забрати іншого ферзя
	bool queenCheckStraight(int a, int b);
	
	// перевірка, чи заданий ферзь може атакувати іншу фігуру по діагоналі
	// true, якщо ферзь може забрати іншого ферзя
	bool queenCheckDiagonal(int a, int b);

	// повертає координати усіх ферзів на дошці
	std::vector<std::vector<int>> getQueenPos();	

	// вставлення ферзя на задану позицію
	void insertQueen(int x, int y);

	// видалення ферзя на заданій позиції
	void removeQueen(int x, int y);	

	// повертає кількість ферзів, що пересікаються між собою
	int getQueenHitNumber();

	// генерація масиву дошок для методів,
	// що з усіх можливих перестановок пар стовпчиків і рядків 
	// мають найменшу кількість ферзів, що пересікаються між собою
	std::vector<ChessBoard*> boardBestArrGen();
	
	// віртуальна функція відображення даних у вікні повідомлення
	virtual void messageBoxShow() {};

	// виведення шахової дошки у файл
	virtual void fileOutput(std::ofstream&);

	// деструктор
	~ChessBoard();
};