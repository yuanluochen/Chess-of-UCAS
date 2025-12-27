#include "chessGame.hpp"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include "decisionTree.hpp"
using namespace std;

/**
 * @brief 棋盘显示函数，重载了运算符 << 
 * 
 * @param os 
 * @param chess chessGame 类的对象
 * @return std::ostream& 
 */
std::ostream & operator<<(std::ostream & os, const chessGame & chess){
  using namespace std;
  const int symBoard = 3;
  const int charBoard = 2;

  //清空终端
  #ifdef SYSTEM_IS_LINUX
  system("clear");
  #endif // DEBUG

  //绘制第一行
  os << setw(symBoard) << " ";
  for (int i = 0; i < chess.chessBoard.col; i++){
    os << setw(charBoard) << char('a' + i); 
  }
  os << endl;
  //绘制剩余
  for (int i = 0; i < chess.chessBoard.row; i++){
    //第一列
    os << setw(symBoard) << i;
    for (int j = 0; j < chess.chessBoard.col; j++){
      int cur = chess.getChessPieceVal(i, j);
      if (cur == BLACK) {
        if (chess.chessPiece_q.back().pos.row == i &&
            chess.chessPiece_q.back().pos.col == j) {
          os << " ■";
        } else {
          os << " ●";
        }

      }
      else if (cur == WRITE){
        if (chess.chessPiece_q.back().pos.row == i &&
            chess.chessPiece_q.back().pos.col == j) {
          os << " □";
        } else {
          os << " ○";
        }
      }
      else{
        if (i == 7 && j == 7) {
          os  << " +";
        } else {
          os <<  setw(symBoard) <<"·";
        }
      }
    }
    os << " " << i;
    os << endl;
  }
  os << setw(symBoard) << " ";
  for (int i = 0; i < chess.chessBoard.col; i++) {
    os << setw(charBoard) << char('a' + i);
  }
  os << endl;
  return os; 
};

/**
 * @brief 获取(row, col)的数值
 * 
 * @param row 行 [0, row - 1]
 * @param col 列 [0, col - 1] 
 * @return int 
 */
int chessGame::getChessPieceVal(int row, int col) const{
  return this->chessBoard.data[row * this->chessBoard.col + col];
}

/**
 * @brief 设置棋子位置同时保存历史数据
 * 
 * @param row 行 [0, this->row - 1]
 * @param col 列 [0, this->col - 1]
 * @return true 设置成功
 * @return false 设置失败
 */
bool chessGame::setChessPiece(int row, int col, chessType chType){
  if (this->getChessPieceVal(row, col) != VOID){
    return false;
  }
  else{
    this->chessBoard.data[row * this->chessBoard.col + col] = chType;
    //存放棋子历史数据
    if (!this->chessPiece_q.empty()){
      chessPiece_q.pop(); 
    }
    chessPiece_q.push({chType, row, col});
  }
  return true;
}

/**
 * @brief 单方向遍历函数 返回连续棋子个数(包含起始棋子)
 * 
 * @param row 行遍历方向
 * @param col 列遍历方向
 * @return int 返回连续棋子(包含起始棋子), -1:还没下棋
 */

int chessGame::singleDirCount(int row, int col) const{
  //判断是否存在当前棋子
  if (this->chessPiece_q.empty()){
    std::cout << "warning: the queue of chessPiece_q is empty, please input chessPiece!" << std::endl;
    return -1;
  } 
  int count = 0;
  auto curChessPiece = this->chessPiece_q.front();
  int curRow = curChessPiece.pos.row;
  int curCol = curChessPiece.pos.col;
  chessType curChtype = curChessPiece.type;
  for (int i = 0; i < 5 && (0 <= curRow && curRow < this->chessBoard.row) &&
                  (0 <= curCol && curCol < this->chessBoard.col);
       i++) {
    if (this->getChessPieceVal(curRow, curCol) == curChtype){
      count++;
    }
    else{
      return count;
    }
    curRow += row;
    curCol += col;
  }
  return count;
}

/**
 * @brief 判断胜利，以新下的棋子为中心位置从八个方向进行判断
 * 
 * @param chtype 棋子类型
 * @return true 胜利
 * @return false 未胜利
 */
bool chessGame::isWin(chessType chtype) const{
  /*
  * l l_u u r_u r r_d d l_d 
  * 0  1  2  3  4  5  6  7
  */
  struct dir {
    int row;
    int col;
  };
  enum DIR { L, L_U, U, R_U, R, R_D, D, L_D };
  //8个遍历方向
  dir dir_a[8] = {
    {0, -1}, 
    {-1, -1},
    {-1, 0},
    {-1, 1},
    {0, 1},
    {1, 1},
    {1, 0},
    {1, -1}
  };
  //四个方向的遍历函数 水平 竖直 左上-右下 右上-左下
  int count_1 = this->singleDirCount(dir_a[L].row, dir_a[L].col) + this->singleDirCount(dir_a[U].row, dir_a[U].col) - 1;
  int count_2 = this->singleDirCount(dir_a[U].row, dir_a[U].col) + this->singleDirCount(dir_a[D].row, dir_a[D].col) - 1;
  int count_3 = this->singleDirCount(dir_a[L_U].row, dir_a[L_U].col) + this->singleDirCount(dir_a[R_D].row, dir_a[R_D].col) - 1;
  int count_4 = this->singleDirCount(dir_a[R_U].row, dir_a[R_U].col) + this->singleDirCount(dir_a[L_D].row, dir_a[L_D].col) - 1;
  
  if (count_1 >= 5 || count_2 >= 5 || count_3 >= 5 || count_4 >= 5)
    return true;
  else
    return false;
}

/**
 * @brief 判断棋盘是否已满
 * 
 * @return true 棋盘已满
 * @return false 棋盘未满
 */
bool chessGame::isBoardFull() const {
    for (int i = 0; i < chessBoard.row * chessBoard.col; i++) {
        if (chessBoard.data[i] == VOID) {
            return false;
        }
    }
    return true;
}

/**
 * @brief 获取可用的移动位置
 * 
 * @return std::vector<std::pair<int, int>> 可用位置列表
 */
std::vector<std::pair<int, int>> chessGame::getAvailableMoves() const {
    std::vector<std::pair<int, int>> moves;
    for (int i = 0; i < chessBoard.row; i++) {
        for (int j = 0; j < chessBoard.col; j++) {
            if (getChessPieceVal(i, j) == VOID) {
                moves.push_back({i, j});
            }
        }
    }
    return moves;
}

/**
 * @brief 下棋函数 包括棋子输入和判断胜负
 * 
 * @param chty 棋子类型
 * @return true 赢
 * @return false 没赢
 */
bool chessGame::playChess(chessType chty) {
  if (chty == BLACK) {
    cout << "●'s player chess:= (输入格式(0~14) (a~o)例如 (9 a))" << std::endl;
  } else {
    cout << "○'s player chess:= (输入格式(0~14) (a~o)例如 (9 a))" << std::endl;
  }
  int row;
  char col;
  cin >> row;
  cin >> col;
  while (1) {
    if (!(row >= 0 && row <= 14 && col >= 'a' && col <= 'o')) {
      cout << "输入格式错误， 输入格式(0~14) (a~o)例如 (9 a), 请重新输入:" << endl;
      cin >> row;
      cin >> col;
    } else {
      if (!this->setChessPiece(row, col - 'a', chty)) {
        // 这个位置有棋子要重新输入
        cout << "输入位置有棋子, 请换个位置输入:" << endl;
        cin >> row;
        cin >> col;
      } else {
        break;
      }
    }
  }
  if (this->isWin(chty)) {
    cout << *this << endl;
    if (chty == BLACK)
      cout << "●'s player is win" << endl;
    else
      cout << "○'s player is win" << endl;
    return true;
  }
  return false;
}

/**
 * @brief ai下棋函数
 * 
 * @param chty 棋子类型
 * @return true 赢
 * @return false 没赢
 */
bool chessGame::aiPlayChess(chessType chty) {
  DecisionTree ai(*this, 4, chty);
  auto bestMove = ai.getBestMove();
  this->setChessPiece(bestMove.first, bestMove.second, chty);
  if (this->isWin(WRITE)) {
    cout << *this << endl;
    cout << "AI is win" << endl;
    return true;
  }
  return false;
}
/**
 * @brief 人人对战
 * 
 * @return int 胜利方的枚举值
 */
int chessGame::man_to_man() {
  while (1) {
    cout << *this << endl;
    if (playChess(BLACK)) {
      return BLACK;
    }
    cout << *this << endl;
    if (playChess(WRITE)) {
      return WRITE;
    }
  }
}

/**
 * @brief 人机对战
 * 
 * @return int 胜利一方枚举值
 */
int chessGame::man_to_ai() {
  cout << "请选择棋子，● = 0, ○ = 1:" << endl;
  chessType chty;
  int temp = 0;
  cin >> temp;
  while (temp != 0 && temp != 1) {
    cout << "输入错误，请重新输入(● = 0, ○ = 1)：" << endl;
    cin >> temp;
  }
  if (temp == 0) {
    chty = BLACK;
  } else {
    chty = WRITE;
  }
  while (1) {
    if (chty == BLACK) {
      cout << *this << endl;
      if (playChess(BLACK)) {
        return BLACK;
      }
      cout << *this << endl;
      if (aiPlayChess(WRITE)) {
        return WRITE;
      }
    } else {
      cout << *this << endl;
      if (aiPlayChess(BLACK)) {
        return BLACK;
      }
      cout << *this << endl;
      if (playChess(WRITE)) {
        return WRITE;
      }
    }
  }
}