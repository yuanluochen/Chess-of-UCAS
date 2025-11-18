#include <iostream>
#include <ostream>
#include "chessGame.hpp"
#include "decisionTree.hpp"
using namespace std;

int main(){
  chessGame game(15); // 创建15x15的棋盘
  while (1){
    std::cout << "play chess:=" << std::endl;
    char row, col;
    cin >> row;
    cin >> col;
    game.setChessPiece(row - '0', col - 'a', WRITE);
    cout << game << endl;
    DecisionTree ai(game, 3, BLACK); // 深度为3，AI执黑
    auto bestMove = ai.getBestMove();
    game.setChessPiece(bestMove.first, bestMove.second, BLACK);
    cout << game << endl;
  }
  
  return 0;
}