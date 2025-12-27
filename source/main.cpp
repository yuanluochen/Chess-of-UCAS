#include <iostream>
#include <ostream>
#include "chessGame.hpp"
#include "decisionTree.hpp"
using namespace std;

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