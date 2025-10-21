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


class graph {
protected:
  std::vector<std::list<int>> vexNode;
public:
  graph();
  friend std::ostream & operator<<(std::ostream & os, const graph & g);
  //元素添加
  int addNode(int srcIndex, int data);
  void display() { std::cout << *this; }
};

class decisionTree : public graph{
public:
  decisionTree();  
};
