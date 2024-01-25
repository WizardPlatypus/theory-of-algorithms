#include <iostream>
#include <stdint.h>
#include <vector>

struct Node {
  char symbol;
  Node *left_node;
  Node *right_node;

  Node *left(char symbol = '-') {
    if (this->left_node == nullptr) {
      this->left_node = new Node{symbol, nullptr, this};
    }
    return this->left_node;
  }

  Node *right(char symbol = '-') {
    if (this->right_node == nullptr) {
      this->right_node = new Node{symbol, this, nullptr};
    }
    return this->right_node;
  }
};

Node* init_nodes(const std::vector<uint64_t> &list) {
  if (list.size() == 0) {
    return new Node{'-', nullptr, nullptr};
  }

  Node *first = new Node{'|', nullptr, nullptr};
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

int main() {
  std::vector<uint64_t> nums{3, 4};
  Node *first = init_nodes(nums);
  Node *curr = first;
  do {
    std::cout << curr->symbol;
    curr = curr->right_node;
  } while (curr != nullptr);
  std::cout << std::endl;
  return 0;
}
