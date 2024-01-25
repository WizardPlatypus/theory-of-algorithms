#include "node.hpp"

Node *init_nodes(const std::vector<uint64_t> &list) {
  if (list.size() == 0) {
    return new Node('-');
  }

  Node *first = new Node('|');
  Node *curr = first;
  for (int i = 1; i < list[0]; i++) {
    curr = curr->right('|');
  }

  if (list.size() == 1) {
    return first;
  }

  for (int j = 1; j < list.size(); j++) {
    curr = curr->right('#');
    for (int i = 0; i < list[j]; i++) {
      curr = curr->right('|');
    }
  }
  return first;
}

Node::Node(char symbol, int index, Node *left_node, Node *right_node) {
  this->symbol = symbol;
  this->index = index;
  this->left_node = left_node;
  this->right_node = right_node;
}

Node *Node::left(char symbol) {
  if (this->left_node == nullptr) {
    this->left_node = new Node(symbol, this->index - 1, nullptr, this);
  }
  return this->left_node;
}

Node *Node::right(char symbol) {
  if (this->right_node == nullptr) {
    this->right_node = new Node(symbol, this->index + 1, this, nullptr);
  }
  return this->right_node;
}
