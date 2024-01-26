#include "../hpp/cell.hpp"
#include "../hpp/move.hpp"
#include "../hpp/node.hpp"
#include "../hpp/rule.hpp"
#include "../hpp/state.hpp"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <regex>
#include <sstream>
#include <stdint.h>
#include <vector>

void display(Node *curr, std::ostream &out = std::cout);
std::map<RuleKey, RuleValue> parse_rules(const char *file);

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    std::cerr << "Expected program path.";
    exit(1);
  }

  auto rules = parse_rules(argv[1]);
  for (auto &rule : rules) {
    rule.first.write(std::cout);
    std::cout << "->";
    rule.second.write(std::cout);
    std::cout << std::endl;
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

  State state{0, false};
  while (1) {
    // std::cout << 'q' << state << std::endl;
    display(curr);

    if (std::abs(curr->index) > 20) {
      std::cout << "Reached node #" << curr->index << std::endl;
      break;
    }

    if (state.is_final) {
      std::cout << "Reached final state" << std::endl;
      break;
    }

    RuleKey key{state, curr->cell};
    if (!rules.contains(key)) {
      std::cout << "No match for ";
      state::write(key.state);
      cell::write(key.cell);
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
    cell::write(node->cell, out);
    node = node->right_node;
  }
  out << std::endl;

  for (int i = 0; i < position; i++) {
    out << ' ';
  }
  out << '^' << std::endl;
}

std::map<RuleKey, RuleValue> parse_rules(const char *path) {
  std::fstream file(path);
  std::string content;
  content.assign((std::istreambuf_iterator<char>(file)),
                 (std::istreambuf_iterator<char>()));

  std::regex rule_regex("q(\\d+|\\*)([|#A])->q(\\d+|\\*)([|#A])([RL])?");
  auto begin = std::sregex_iterator(content.begin(), content.end(), rule_regex);
  auto end = std::sregex_iterator();

  std::map<RuleKey, RuleValue> rules;
  for (auto i = begin; i != end; i++) {
    std::smatch match = *i;
    std::stringstream buffer;
    RuleKey key;
    RuleValue value;

    buffer << match[1] << ' ' << match[2];
    key.read(buffer);

    buffer << match[3] << ' ' << match[4] << ' ' << match[5];
    value.read(buffer);

    rules[key] = value;
  }

  return rules;
}
