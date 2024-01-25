#include <cstddef>
#include <iostream>
#include <istream>
#include <map>
#include <stdint.h>
#include <vector>

struct Node {
  char symbol;
  Node *left_node;
  Node *right_node;
  int index;

  Node(char symbol, int index = 0, Node *left_node = nullptr,
       Node *right_node = nullptr) {
    this->symbol = symbol;
    this->index = index;
    this->left_node = left_node;
    this->right_node = right_node;
  }

  Node *left(char symbol = '-') {
    if (this->left_node == nullptr) {
      this->left_node = new Node(symbol, this->index - 1, nullptr, this);
    }
    return this->left_node;
  }

  Node *right(char symbol = '-') {
    if (this->right_node == nullptr) {
      this->right_node = new Node(symbol, this->index + 1, this, nullptr);
    }
    return this->right_node;
  }
};

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

struct Rule {
  char state_in;
  char symbol_in;
  char state_out;
  char symbol_out;
  // move > 0 => right
  // move < 0 => left
  // move == 0 => stay
  int8_t move;
};

std::istream &operator>>(std::istream &in, Rule &rule) {
  in >> rule.state_in >> rule.symbol_in >> rule.state_out >> rule.symbol_out >>
      rule.move;
  return in;
}

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
  /*
  std::vector<uint64_t> nums{3, 4};
  Node *first = init_nodes(nums);
  Node *curr = first;
  do {
    std::cout << curr->symbol;
    curr = curr->right_node;
  } while (curr != nullptr);
  std::cout << std::endl;
  return 0;
  */
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
}
