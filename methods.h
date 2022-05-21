#pragma once
#include <iostream>
#include <queue>
#include "ChessBoard.h"
#include "Tree.h"

ChessBoard* LDFS(ChessBoard* main);
ChessBoard* BFS(ChessBoard* main);
ChessBoard* IDS(ChessBoard* main, int max_depth = ChessBoard::FIELD_SIZE);
TreeNode* DLS(TreeNode* src, int limit, int pos = 0);