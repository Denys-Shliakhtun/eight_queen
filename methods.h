#pragma once
#include <iostream>
#include <queue>
#include <stack>
#include "ChessBoardStat.h"
#include "TreeNode.h"

// реалізація методу LDFS для розв’язання задачі про 8 ферзів
ChessBoardStat* LDFS(ChessBoard* main);

// реалізація методу BFS для розв’язання задачі про 8 ферзів
ChessBoardStat* BFS(ChessBoard* main);

// реалізація методу IDS для розв’язання задачі про 8 ферзів
ChessBoardStat* IDS(ChessBoard* main, int max_depth);

// рекурсивна функція для реалізації методу IDS
Local::TreeNode* DLS(Local::TreeNode* src, int limit);