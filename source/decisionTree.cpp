#include "decisionTree.hpp"

/**
 * @brief 节点添加函数
 * 
 * @param srcIndex 父节点的下标
 * @param data 该节点的数据
 * @return int 当前节点的下标
 */
int graph::addNode(int srcIndex, int data) {
  std::list<int> node;
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
}

std::ostream & operator<<(std::ostream & os, const graph & g){
  for (int i = 0; i < g.vexNode.size(); i++){
    for (auto iter = g.vexNode[i].begin(); iter != g.vexNode[i].end(); iter++) {
      os << *iter << " -> ";
    }
    os << std::endl;
  }
  return os;
}