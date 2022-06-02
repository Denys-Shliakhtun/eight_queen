#pragma once
#include <iostream>
#include <queue>
#include <stack>
#include "ChessBoard.h"
#include "Tree.h"

ChessBoard* LDFS(ChessBoard* main);
ChessBoard* BFS(ChessBoard* main);
ChessBoard* IDS(ChessBoard* main, int max_depth);
TreeNode* DLS(TreeNode* src, int limit);