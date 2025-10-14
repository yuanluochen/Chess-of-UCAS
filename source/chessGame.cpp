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


/**
 * @brief 判断胜利
 * 
 * @param chtype 棋子类型
 * @return true 胜利
 * @return false 未胜利
 */
bool chessGame::isWin(chessType chtype) const{
  //遍历判断五子
  int rowBias[4] = {1, 1, 0, -1};
  int colBias[4] = {0, 1, 1, 1};
  //四轮遍历
  int count = 0;//连续棋子计算
  for (int k = 0; k < 4; k++){
    int curRow = 0, curCol = 0;
    if (k < 2){
      // 0列 -> (col - 1)列
      for (int i = 0; i < this->chessBoard.col; i++){
        count = 0;//初始化
        curRow = 0;
        curCol = i;
        for (int j = 0;
             (0 <= curRow && curRow < this->chessBoard.row) && (0 <= curCol && curCol < this->chessBoard.col);
             j++){
          //位置更新
          curRow += rowBias[k];
          curCol += colBias[k];
          if (getChessPieceVal(curRow, curCol) == chtype){
            count++;  
            if (count >= 5){
              return true;
            }
          }
          else{
            count = 0; 
          }
        }
      } 
    }
    else{
      // (row - 1)行 -> 0行
      for (int i = this->chessBoard.row - 1; i >= 0; i--) {
        count = 0; //初始化
        curRow = i;
        curCol = 0;
        for (int j = 0;
             (0 <= curRow && curRow < this->chessBoard.row) && (0 <= curCol && curCol < this->chessBoard.col);
             j++){
          //位置更新
          curRow += rowBias[k];
          curCol += colBias[k];
          if (getChessPieceVal(curRow, curCol) == chtype){
            count++;
            if (count >= 5){
              return true;
            }  
          }
          else{
            count = 0; 
          }
        }
      }
    }
  }
  return false;  
}
