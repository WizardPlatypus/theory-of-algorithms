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

uint64_t write_tape(Node *node, std::ostream &out = std::cout);
void write_marker(int position, std::ostream &out = std::cout);
void write_rule(const RuleKey &key, const RuleValue &value,
                std::ostream &out = std::cout);
std::map<RuleKey, RuleValue> parse_rules(const char *file);

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    std::cerr << "Expected program path.";
    exit(1);
  }

  auto rules = parse_rules(argv[1]);
  /*
  for (auto &rule : rules) {
    write_rule(rule.first, rule.second);
    std::cout << std::endl;
  }
  // */

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

  int position = write_tape(curr);
  std::cout << std::endl;
  write_marker(position);
  std::cout << std::endl;

  RuleKey key;
  RuleValue value;

  std::stringstream buffer;
  std::string s;

  while (1) {
    if (std::abs(curr->index) > 20) {
      std::cout << "Reached node #" << curr->index << std::endl;
      break;
    }

    if (state.is_final) {
      std::cout << "Reached final state" << std::endl;
      break;
    }

    key = RuleKey{state, curr->cell};
    if (!rules.contains(key)) {
      std::cout << "No match for ";
      state::write(key.state);
      cell::write(key.cell);
      std::cout << std::endl;
      break;
    }

    value = rules[key];
    state = value.state;
    curr->cell = value.cell;
    if (value.move == Move::Right) {
      curr = curr->right();
    } else if (value.move == Move::Left) {
      curr = curr->left();
    }

    write_rule(key, value, buffer);
    buffer >> s;
    std::cout << s << ' ';
    position = write_tape(curr);
    std::cout << std::endl;
    write_marker(position + 1 + s.size());
    std::cout << std::endl;
    buffer.clear();
    s.clear();
  }
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

uint64_t write_tape(Node *node, std::ostream &out) {
  uint64_t position = 0;
  while (node->left_node != nullptr) {
    node = node->left_node;
    position++;
  }

  while (node != nullptr) {
    cell::write(node->cell, out);
    node = node->right_node;
  }

  return position;
}

void write_marker(int position, std::ostream &out) {
  for (int i = 0; i < position; i++) {
    out << ' ';
  }
  out << '^';
}

void write_rule(const RuleKey &key, const RuleValue &value, std::ostream &out) {
  key.write(out);
  out << "->";
  value.write(out);
}
