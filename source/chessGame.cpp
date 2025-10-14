#include "chessGame.hpp"
#include <iomanip>


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
  //绘制第一行
  os << setw(symBoard) << " ";
  for (int i = 0; i < chess.chessBoard.col; i++){
    os << setw(charBoard) << i; 
  }
  os << endl;
  //绘制剩余
  for (int i = 0; i < chess.chessBoard.row; i++){
    //第一列
    os << setw(symBoard) << i;
    for (int j = 0; j < chess.chessBoard.col; j++){
      int cur = chess.getChessPieceVal(i, j);
      if (cur == BLACK){
        os << setw(charBoard) << 'x';    
      }
      else if (cur == WRITE){
        os << setw(charBoard) << 'o';
      }
      else{
        os << setw(symBoard) << "·";
      }
    }
    os << endl;
  }
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
 * @brief Set the Chess Piece object
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
  else
    this->chessBoard.data[row * this->chessBoard.col + col] = chType;
  return true;
}