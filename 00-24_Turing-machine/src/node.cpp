#include "node.hpp"
#include <istream>
#include <ostream>

std::istream &operator>>(std::istream &in, Cell &cell) {
  char c;
  in >> c;
  if (c == '|') {
    cell = Cell::Stick;
  } else if (c == '#') {
    cell = Cell::Sharp;
  } else {
    cell = Cell::Empty;
  }
  return in;
}

std::ostream &operator<<(std::ostream &out, const Cell &cell) {
  char c;
  if (cell == Cell::Stick) {
    c = '|';
  } else if (cell == Cell::Sharp) {
    c = '#';
  } else {
    c = '-';
  }
  out << c;
  return out;
}

Node *init_nodes(const std::vector<uint64_t> &list) {
  if (list.size() == 0) {
    return new Node(Cell::Empty);
  }

  Node *first = new Node(Cell::Stick);
  Node *curr = first;
  for (int i = 1; i < list[0]; i++) {
    curr = curr->right(Cell::Stick);
  }

  if (list.size() == 1) {
    return first;
  }

  for (int j = 1; j < list.size(); j++) {
    curr = curr->right(Cell::Sharp);
    for (int i = 0; i < list[j]; i++) {
      curr = curr->right(Cell::Stick);
    }
  }
  return first;
}

Node::Node(Cell cell, int index, Node *left_node, Node *right_node) {
  this->cell = cell;
  this->index = index;
  this->left_node = left_node;
  this->right_node = right_node;
}

Node *Node::left(Cell cell) {
  if (this->left_node == nullptr) {
    this->left_node = new Node(cell, this->index - 1, nullptr, this);
  }
  return this->left_node;
}

Node *Node::right(Cell cell) {
  if (this->right_node == nullptr) {
    this->right_node = new Node(cell, this->index + 1, this, nullptr);
  }
  return this->right_node;
}
