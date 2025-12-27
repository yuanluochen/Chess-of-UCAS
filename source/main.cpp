#include <iostream>
#include <ostream>
#include "chessGame.hpp"
#include "decisionTree.hpp"
using namespace std;
void man_machine(chessGame & game) {
  while (1){
    cout << game << endl;
    std::cout << "player chess:=" << std::endl;
    char row, col;
    cin >> row;
    cin >> col;
    game.setChessPiece(row - '0', col - 'a', WRITE);
    cout << game << endl;
    DecisionTree ai(game, 3, BLACK); // 深度为3，AI执黑
    auto bestMove = ai.getBestMove();
    game.setChessPiece(bestMove.first, bestMove.second, BLACK);
  }
}

int main(){
  chessGame game(15); // 创建15x15的棋盘
  int mode = true;
  cout << "请输入下棋模式，（人机对战=1， 人人对战=2， 退出=0):" << endl;
  cin >> mode;
  
  switch (mode) {
  case 0:
    cout << "游戏退出" << endl;
    break;
  case 1:
    game.man_to_ai();
    break;
  case 2:
    game.man_to_man();
    break;
  }
  
  return 0;
}