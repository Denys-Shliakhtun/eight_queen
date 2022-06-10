#pragma once
#include <iostream>
#include <queue>
#include <stack>
#include "ChessBoardStat.h"
#include "TreeNode.h"
ChessBoardStat* LDFS(ChessBoard* main);
ChessBoardStat* BFS(ChessBoard* main);
ChessBoardStat* IDS(ChessBoard* main, int max_depth);
Local::TreeNode* DLS(Local::TreeNode* src, int limit);