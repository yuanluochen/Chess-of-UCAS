// 实现 decisionTree.cpp
#include "decisionTree.hpp"

// 评估函数实现
int DecisionTree::evaluateBoard(const chessGame& game) const {
    int score = 0;
    int boardSize = game.getBoardSize();
    
    // 检查每个位置的四方向连线
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            int piece = game.getChessPieceVal(i, j);
            if (piece == VOID) continue;
            
            // 水平方向
            int horizontal = 1;
            for (int k = 1; k < 5 && j + k < boardSize; k++) {
                if (game.getChessPieceVal(i, j + k) == piece) horizontal++;
                else break;
            }
            
            // 垂直方向
            int vertical = 1;
            for (int k = 1; k < 5 && i + k < boardSize; k++) {
                if (game.getChessPieceVal(i + k, j) == piece) vertical++;
                else break;
            }
            
            // 对角线（右下）
            int diag1 = 1;
            for (int k = 1; k < 5 && i + k < boardSize && j + k < boardSize; k++) {
                if (game.getChessPieceVal(i + k, j + k) == piece) diag1++;
                else break;
            }
            
            // 对角线（左下）
            int diag2 = 1;
            for (int k = 1; k < 5 && i + k < boardSize && j - k >= 0; k++) {
                if (game.getChessPieceVal(i + k, j - k) == piece) diag2++;
                else break;
            }
            
            // 根据连线长度给分
            int maxLine = std::max({horizontal, vertical, diag1, diag2});
            int directionScore = 0;
            
            if (maxLine >= 5) directionScore = 100000; // 五连
            else if (maxLine == 4) directionScore = 1000; // 四连
            else if (maxLine == 3) directionScore = 100; // 三连
            else if (maxLine == 2) directionScore = 10; // 二连
            
            // 根据玩家调整分数
            if (piece == aiPlayer) {
                score += directionScore;
            } else {
                score -= directionScore;
            }
        }
    }
    
    return score;
}

std::vector<std::pair<int, int>> DecisionTree::generateMoves(const chessGame& game) const {
    std::vector<std::pair<int, int>> moves;
    int boardSize = game.getBoardSize();
    
    // 首先收集所有空位
    std::vector<std::pair<int, int>> allEmpty;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (game.getChessPieceVal(i, j) == VOID) {
                allEmpty.push_back({i, j});
            }
        }
    }
    
    // 如果有棋子，优先考虑已有棋子周围的位置
    bool hasPieces = false;
    for (int i = 0; i < boardSize && !hasPieces; i++) {
        for (int j = 0; j < boardSize && !hasPieces; j++) {
            if (game.getChessPieceVal(i, j) != VOID) {
                hasPieces = true;
            }
        }
    }
    
    if (hasPieces) {
        // 计算每个空位到最近棋子的距离
        std::vector<std::pair<int, std::pair<int, int>>> scoredMoves;
        
        for (const auto& pos : allEmpty) {
            int minDistance = INT_MAX;
            
            // 找到最近的棋子
            for (int i = 0; i < boardSize; i++) {
                for (int j = 0; j < boardSize; j++) {
                    if (game.getChessPieceVal(i, j) != VOID) {
                        int dist = std::abs(i - pos.first) + std::abs(j - pos.second);
                        if (dist < minDistance) {
                            minDistance = dist;
                        }
                    }
                }
            }
            
            // 距离越近，分数越高（优先级越高）
            int score = -minDistance; // 负号因为我们要按降序排序
            scoredMoves.push_back({score, pos});
        }
        
        // 按分数排序
        std::sort(scoredMoves.begin(), scoredMoves.end(), 
                  [](const auto& a, const auto& b) { return a.first > b.first; });
        
        // 只取前20个最佳位置（为了性能）
        int count = std::min(20, (int)scoredMoves.size());
        for (int i = 0; i < count; i++) {
            moves.push_back(scoredMoves[i].second);
        }
    } else {
        // 棋盘为空，选择中心位置
        moves.push_back({boardSize / 2, boardSize / 2});
    }
    
    return moves;
}

int DecisionTree::alphaBeta(chessGame& game, int depth, int alpha, int beta, bool maximizingPlayer) {
    // 终止条件：达到最大深度或游戏结束
    if (depth == 0 || game.isWin(BLACK) || game.isWin(WRITE) || game.isBoardFull()) {
        return evaluateBoard(game);
    }
    
    std::vector<std::pair<int, int>> moves = generateMoves(game);
    
    if (maximizingPlayer) {
        int maxEval = INT_MIN;
        
        for (const auto& move : moves) {
            chessGame newGame = game; // 复制当前游戏状态
            
            // AI下棋
            if (newGame.setChessPiece(move.first, move.second, aiPlayer)) {
                int eval = alphaBeta(newGame, depth - 1, alpha, beta, false);
                maxEval = std::max(maxEval, eval);
                alpha = std::max(alpha, eval);
                
                if (beta <= alpha) {
                    break; // Beta剪枝
                }
            }
        }
        
        return maxEval;
    } else {
        int minEval = INT_MAX;
        chessType opponent = (aiPlayer == BLACK) ? WRITE : BLACK;
        
        for (const auto& move : moves) {
            chessGame newGame = game; // 复制当前游戏状态
            
            // 对手下棋
            if (newGame.setChessPiece(move.first, move.second, opponent)) {
                int eval = alphaBeta(newGame, depth - 1, alpha, beta, true);
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
            int moveValue = alphaBeta(newGame, maxDepth - 1, INT_MIN, INT_MAX, false);
            
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