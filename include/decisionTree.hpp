/**
 * @file decisionTree.hpp 决策树
 * @author yuanluochen (yuanluochen@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <list>
#include <vector>
#include <iostream>
#include "chessGame.hpp"

/**
 * @brief 用邻接表实现的图
 * 
 */
template <typename T> class graph {
protected:
  std::vector<std::list<T>> vexNode;
public:
  graph(){};

  graph(graph &) = delete;
  graph & operator=(graph &) = delete;

  friend std::ostream & operator<<(std::ostream & os, const graph<T> & g){
    for (int i = 0; i < g.vexNode.size(); i++) {
      for (auto iter = g.vexNode[i].begin(); iter != g.vexNode[i].end();
           iter++) {
        os << *iter << " -> ";
      }
      os << std::endl;
    }
    return os;
  }
  /**
   * @brief 节点添加函数
   *
   * @param srcIndex 父节点的下标
   * @param data 该节点的数据
   * @return int 当前节点的下标
   */
  int addNode(int srcIndex, T data) {
    std::list<T> node;
    node.push_back(data);
    this->vexNode.push_back(node);
    if (srcIndex >= 0) {
      if (srcIndex >= vexNode.size()) {
        std::cerr << "warning: the parent's Node index is not exist."
                  << std::endl;
      } else {
        this->vexNode[srcIndex].push_back(data);
      }
    }
    return this->vexNode.size() - 1;
  };
  void display() { std::cout << *this; }
};

struct TreeNode{
  int row;
  int col;
  int score;
};

class decisionTree : public graph<TreeNode>{
private:
  chessGame baseChess;
  int lastIdx;
public:
  decisionTree(chessGame &base) : baseChess(base) {
  };
};
