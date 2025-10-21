#pragma once
#include <iostream>
#include <ostream>
#include <queue>

//函数清空根据系统进行选择
#define SYSTEM_IS_LINUX 1

enum chessType { 
  BLACK = 1, 
  WRITE = -1, 
  VOID = 0 
};
class chessPiece {
public:
  // 类型
  chessType type;
  // 位置
  struct {
    int row;
    int col;
  } pos;

public:
  chessPiece(chessType type, int rowPos, int colPos)
      : type(type), 
        pos({
          rowPos, 
          colPos
        }) {};
};

class chessGame {
private:
  // 棋盘
  struct {
    int row;   // 行
    int col;   // 列
    int *data; // 棋盘数据
  } chessBoard;
  // 棋子历史数据
  std::queue<chessPiece> chessPiece_q;

public:
  //构造函数 由于英文字母仅有26个所以列最大26，当大于26时col为26, 为保证棋盘为正方形 row 也是同样的规则
  chessGame(int size) : chessBoard({size, size}) {
    if (size > 26){
      std::cout << "warning: max value of row or col is 26!" << std::endl;
      this->chessBoard.row = 26;
      this->chessBoard.col = 26;
    }
    // 初始化并且清空棋盘
    this->chessBoard.data =
        new int[this->chessBoard.row * this->chessBoard.col]{};
  }

  chessGame(chessGame &) = delete;
  chessGame &operator=(chessGame &) = delete;

  ~chessGame() { delete[] this->chessBoard.data; }
  // 显示棋盘数据
  friend std::ostream & operator<<(std::ostream & os, const chessGame & chess);
  //获取对应位置的棋子数值
  int getChessPieceVal(int row, int col) const;
  //设置棋子位置
  bool setChessPiece(int row, int col, chessType chtype);
  //判断胜利
  bool isWin(chessType chtype) const;

private:
  //单个方向遍历函数，返回该方向连续棋子个数
  int singleDirCount(int row, int col) const;
  
};