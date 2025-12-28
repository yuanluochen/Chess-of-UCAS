/**
 * @file chessGame.hpp 五子棋类
 * @author yuanluochen
 * @brief 
 * @version 0.1
 * @date 2025-12-27
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once
#include <iostream>
#include <ostream>
#include <queue>
#include <utility>
#include <vector>

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
  //构造函数
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

  // 默认构造函数
  chessGame() : chessBoard({15, 15}) {
    this->chessBoard.data = new int[15 * 15]{};
  }

  //拷贝构造和赋值操作重载
  chessGame & operator=(const chessGame & ch){
    if (this != &ch) {
      delete[] this->chessBoard.data;
      this->chessBoard.row = ch.chessBoard.row;
      this->chessBoard.col = ch.chessBoard.col;
      this->chessBoard.data = new int[this->chessBoard.row * this->chessBoard.col];
      for (int i = 0; i < this->chessBoard.row * this->chessBoard.col; i++) {
        this->chessBoard.data[i] = ch.chessBoard.data[i];
      }
      this->chessPiece_q = ch.chessPiece_q;
    }
    return *this;
  }
  
  chessGame(const chessGame &ch) { 
    this->chessBoard.row = ch.chessBoard.row;
    this->chessBoard.col = ch.chessBoard.col;
    this->chessBoard.data = new int[this->chessBoard.row * this->chessBoard.col];
    for (int i = 0; i < this->chessBoard.row * this->chessBoard.col; i++) {
      this->chessBoard.data[i] = ch.chessBoard.data[i];
    }
    this->chessPiece_q = ch.chessPiece_q;
  }

  ~chessGame() { delete[] this->chessBoard.data; }
  // 玩家下棋函数
  bool playChess(chessType);

  bool aiPlayChess(chessType);

  // 人人对战
  int man_to_man();

  //人机对战
  int man_to_ai();
  
  // 显示棋盘数据
  friend std::ostream & operator<<(std::ostream & os, const chessGame & chess);
  
  //获取对应位置的棋子数值
  int getChessPieceVal(int row, int col) const;
  
  //设置棋子位置
  bool setChessPiece(int row, int col, chessType chtype);
  
  //判断胜利
  bool isWin(chessType chtype) const;

  // 计算最大连子数
  int getMaxNumPieces(chessType chtype) const;
  
  // 获取棋盘尺寸
  std::pair<int, int> getBoardSize() const { return {chessBoard.row, chessBoard.col}; }
  
  // 判断棋盘是否已满
  bool isBoardFull() const;
  
  // 获取可用的移动位置
  std::vector<std::pair<int, int>> getAvailableMoves() const;

private:
  //单个方向遍历函数，返回该方向连续棋子个数
  int singleDirCount(int row, int col) const;
};