#include <cstddef>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <stdint.h>
#include <vector>
#include "node.hpp"
#include "rule.hpp"

int main(int argc, const char* argv[]) {
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
  std::cout << "Yay!" << std::endl;
}
