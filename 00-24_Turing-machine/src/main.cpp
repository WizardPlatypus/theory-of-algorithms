#include <cstddef>
#include <iostream>
#include <istream>
#include <map>
#include <stdint.h>
#include <vector>
#include "node.hpp"

struct RuleKey {
  char state;
  char symbol;

  bool operator==(const RuleKey &other) const {
    return this->state == other.state && this->symbol == other.symbol;
  }

  bool operator<(const RuleKey &other) const {
    if (this->state == other.state) {
      return this->symbol < other.symbol;
    }
    return this->state < other.state;
  }
};

std::istream &operator>>(std::istream &in, RuleKey &key) {
  in >> key.state >> key.symbol;
  return in;
}

enum Move {
  Left,
  Right,
  None
};
  
std::istream & operator>>(std::istream & in, Move & move) {
  char c;
  in >> c;
  if (c == 'L') {
    move = Move::Left;
  } else if (c == 'R') {
    move = Move::Right;
  } else {
    move = Move::None;
  }
  return in;
}

struct RuleValue {
  char state;
  char symbol;
  Move move;
};

std::istream &operator>>(std::istream &in, RuleValue &value) {
  in >> value.state >> value.symbol >> value.move;
  return in;
}

int main() {
  // /*
  std::vector<uint64_t> nums{3, 4};
  Node *first = init_nodes(nums);
  Node *curr = first;
  do {
    std::cout << curr->symbol;
    curr = curr->right_node;
  } while (curr != nullptr);
  std::cout << std::endl;
  return 0;
  // */
  /*
  std::map<RuleKey, RuleValue> rules;
  for (int i = 0; i < 3; i++) {
    RuleKey key;
    RuleValue value;
    std::cin >> key >> value;
    rules[key] = value;
  }

  for (const auto &rule : rules) {
    std::cout << "q" << rule.first.state << rule.first.symbol << " -> q"
              << rule.second.state << rule.second.symbol;
    if (rule.second.move > 0) {
      std::cout << "R";
    } else if (rule.second.move < 0) {
      std::cout << "L";
    }
    std::cout << std::endl;
  }
  */
}
