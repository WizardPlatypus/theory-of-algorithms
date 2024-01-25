#pragma once
#include <stdint.h>
#include <vector>

struct Node {
  Node(char symbol, int index = 0, Node *left_node = nullptr,
       Node *right_node = nullptr);
  Node *left(char symbol = '-');
  Node *right(char symbol = '-');

  char symbol;
  Node *left_node;
  Node *right_node;
  int index;
};

Node *init_nodes(const std::vector<uint64_t> &list);
