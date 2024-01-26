#include "../hpp/node.hpp"
#include "../hpp/rule.hpp"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdint.h>
#include <vector>

void display(Node *curr, std::ostream &out = std::cout);

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    std::cerr << "Expected program path.";
    exit(1);
  }

  std::fstream file(argv[1]);
  std::map<RuleKey, RuleValue> rules;
  while (file) {
    RuleKey key;
    RuleValue value;
    key.read(file);
    value.read(file);
    rules[key] = value;
  }

  std::vector<uint64_t> nums;
  for (int i = 0; i + 2 < argc; i++) {
    std::stringstream buffer;
    buffer << argv[i + 2];
    uint64_t value;
    buffer >> value;
    nums.push_back(value);
  }

  Node *first = init_nodes(nums);
  Node *curr = first;

  char state = '0';
  while (1) {
    // std::cout << 'q' << state << std::endl;
    display(curr);

    if (std::abs(curr->index) > 20) {
      std::cout << "Reached node #" << curr->index << std::endl;
      break;
    }

    RuleKey key{state, curr->cell};
    if (!rules.contains(key)) {
      std::cout << "No match for q" << key.state;
      write_cell(std::cout, key.cell);
      std::cout << std::endl;
      break;
    }

    RuleValue value = rules[key];
    state = value.state;
    curr->cell = value.cell;
    if (value.move == Move::Right) {
      curr = curr->right();
    } else if (value.move == Move::Left) {
      curr = curr->left();
    }
  }
}

void display(Node *node, std::ostream &out) {
  int position = 0;
  while (node->left_node != nullptr) {
    node = node->left_node;
    position++;
  }

  while (node != nullptr) {
    write_cell(out, node->cell);
    node = node->right_node;
  }
  out << std::endl;

  for (int i = 0; i < position; i++) {
    out << ' ';
  }
  out << '^' << std::endl;
}
