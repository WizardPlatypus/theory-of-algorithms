#pragma once
#include <stdint.h>
#include <vector>

// | # -
enum Cell { Stick, Sharp, Empty };

struct Node {
  Node(Cell cell = Cell::Empty, int index = 0, Node *left_node = nullptr,
       Node *right_node = nullptr);
  Node *left(Cell cell = Cell::Empty);
  Node *right(Cell cell = Cell::Empty);

  Cell cell;
  Node *left_node;
  Node *right_node;
  int index;
};

Node *init_nodes(const std::vector<uint64_t> &list);
