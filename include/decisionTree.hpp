/**
 * @file decisionTree.hpp 决策树
 * @author yuanluochen (yuanluochen@foxmail.com)
 * @brief 实现五子棋对战的相应功能
 * @version 0.1
 * @date 2025-10-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <list>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
#include "chessGame.hpp"

struct TreeNode{
  int row;
  int col;
  int score;
  chessGame gameState;
  
  TreeNode(int r, int c, int s, const chessGame& game) 
    : row(r), col(c), score(s), gameState(game) {}
};

class DecisionTree {
private:
  chessGame baseChess;
  int maxDepth;
  chessType aiPlayer; // AI玩家的棋子类型
  
public:
  //构造函数
  DecisionTree(const chessGame& base, int depth, chessType ai) 
    : baseChess(base), maxDepth(depth), aiPlayer(ai) {};
  
  // 获取最佳移动
  std::pair<int, int> getBestMove();
  
  // 评估函数 - 给棋盘状态打分
  int evaluateBoard(const chessGame &game, const chessType chty) const;

private:
  // Alpha-Beta 剪枝搜索
  int alphaBeta(chessGame& game, int depth, int alpha, int beta, chessType chty);
  
  // 生成可能的移动
  std::vector<std::pair<int, int>> generateMoves(const chessGame& game) const;
};