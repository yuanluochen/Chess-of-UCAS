// 实现 decisionTree.cpp
#include "decisionTree.hpp"
#include "chessGame.hpp"
#include <cstdlib>
#include <utility>
#include <vector>

// 评估函数实现
int DecisionTree::evaluateBoard(const chessGame& game, const chessType chty) const {
  int score = 0;
  // 根据连线长度给分
  int maxLine = game.getMaxNumPieces();
  int directionScore = 0;

  if (maxLine >= 5)
    directionScore = 100000; // 五连
  else if (maxLine == 4)
    directionScore = 3000; // 四连
  else if (maxLine == 3)
    directionScore = 2900; // 三连
  else if (maxLine == 2)
    directionScore = 10; // 二连

  // 根据玩家调整分数
  if (chty == aiPlayer) {
    score += directionScore;
  } else {
    score -= directionScore;
  }
  return score;
}

std::vector<std::pair<int, int>> DecisionTree::generateMoves(const chessGame& game) const {
    std::vector<std::pair<int, int>> moves;
    int boardSize = game.getBoardSize().first;
    // 首先收集所有空位,和非空位
    std::vector<std::pair<int, int>> allEmpty;
    std::vector<std::pair<int, int>> allNoEmpty;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (game.getChessPieceVal(i, j) == VOID) {
              allEmpty.push_back({i, j});
            } else {
              allNoEmpty.push_back({i, j});
            }
        }
    }
    if (!allNoEmpty.empty()) {
        // 计算每个空位到最近棋子的距离
        std::vector<std::pair<int, std::pair<int, int>>> scoredMoves;
        for (const auto posEmpty : allEmpty) {
            int minDistance = INT_MAX;
            for (const auto posNoEmpty : allNoEmpty) {
              int dist = std::abs(posEmpty.first - posNoEmpty.first) +
                         std::abs(posEmpty.second - posNoEmpty.second);
              //处理一种对角线情况 
              if (std::abs(posEmpty.first - posNoEmpty.first) == 1 &&
                  std::abs(posEmpty.second - posNoEmpty.second) == 1) {
                    dist = 1;
              }
              if (dist < minDistance) {
                minDistance = dist;
              }
            }
            // 距离越近，分数越高（优先级越高）
            int score = -minDistance; // 负号因为我们要按降序排序
            scoredMoves.push_back({score, posEmpty});
        }
        // 按分数排序
        std::sort(scoredMoves.begin(), scoredMoves.end(), 
                  [](const auto& a, const auto& b) { return a.first > b.first; });
        // 只取前n个最佳位置（为了性能）
        int count = std::min(50, (int)scoredMoves.size());
        for (int i = 0; i < count; i++) {
            moves.push_back(scoredMoves[i].second);
        }
    } else {
        // 棋盘为空，选择中心位置
        moves.push_back({boardSize / 2, boardSize / 2});
    }
    
    return moves;
}

int DecisionTree::alphaBeta(chessGame& game, int depth, int alpha, int beta, chessType chty) {
    // 终止条件：达到最大深度或游戏结束
    if (depth == 0 || game.isWin(BLACK) || game.isWin(WRITE) || game.isBoardFull()) {
        return evaluateBoard(game, chty == BLACK ? WRITE : BLACK);
    }
    chessType opponent = (aiPlayer == BLACK) ? WRITE : BLACK;
    std::vector<std::pair<int, int>> moves = generateMoves(game); 
    if (chty == aiPlayer) {
        int maxEval = INT_MIN;  
        for (const auto& move : moves) {
            chessGame newGame = game; // 复制当前游戏状态  
            // AI下棋
            if (newGame.setChessPiece(move.first, move.second, aiPlayer)) {
                int eval = alphaBeta(newGame, depth - 1, alpha, beta, opponent);
                maxEval = std::max(maxEval, eval);
                alpha = std::max(alpha, eval);
                //aplha随着搜索已经变得很大了，大于父亲的beta当前值，beta只会变小，alpha只会变大，所以没必要在通过搜索增加alpha了
                if (beta <= alpha) {
                    break; // Beta剪枝
                }
            }
        }
        return maxEval;
    } else {
        int minEval = INT_MAX;
        for (const auto& move : moves) {
            chessGame newGame = game; // 复制当前游戏状态
            // 对手下棋
            if (newGame.setChessPiece(move.first, move.second, opponent)) {
                int eval = alphaBeta(newGame, depth - 1, alpha, beta, aiPlayer);
                minEval = std::min(minEval, eval);
                beta = std::min(beta, eval);
                if (beta <= alpha) {
                    break; // Alpha剪枝
                }
            }
        }  
        return minEval;
    }
}

std::pair<int, int> DecisionTree::getBestMove() {
    std::vector<std::pair<int, int>> moves = generateMoves(baseChess);
    std::pair<int, int> bestMove = {-1, -1};
    int bestValue = INT_MIN;
    for (const auto& move : moves) {
        chessGame newGame = baseChess; // 复制当前游戏状态
        // 尝试这个移动
        if (newGame.setChessPiece(move.first, move.second, aiPlayer)) {
          // 让对方下棋
          int moveValue = alphaBeta(newGame, maxDepth - 1, INT_MIN, INT_MAX,
                                    (aiPlayer == BLACK) ? WRITE : BLACK);
          if (moveValue > bestValue) {
            bestValue = moveValue;
            bestMove = move;
          }
        }
    }
    // 如果没有找到有效移动，返回第一个可用位置
    if (bestMove.first == -1 && !moves.empty()) {
        bestMove = moves[0];
    }
    return bestMove;
}