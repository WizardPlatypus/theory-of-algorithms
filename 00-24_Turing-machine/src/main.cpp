#include <cstddef>
#include <iostream>
#include <istream>
#include <map>
#include <stdint.h>
#include <vector>
#include "node.hpp"
#include "rule.hpp"

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
  // */
  // /*
  std::map<RuleKey, RuleValue> rules;
  for (int i = 0; i < 3; i++) {
    RuleKey key;
    RuleValue value;
    key.read(std::cin);
    value.read(std::cin);
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
  // */
}
