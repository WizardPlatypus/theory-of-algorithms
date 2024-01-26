#pragma once
#include "cell.hpp"
#include <stdint.h>
#include <vector>

struct Node {
  Node(Cell cell = Cell::Lambda, int index = 0, Node *left_node = nullptr,
       Node *right_node = nullptr);
  Node *left(Cell cell = Cell::Lambda);
  Node *right(Cell cell = Cell::Lambda);

  Cell cell;
  Node *left_node;
  Node *right_node;
  int index;
};

Node *init_nodes(const std::vector<uint64_t> &list);
