#pragma once
#include <iostream>
#include <stdint.h>

struct State {
  bool operator==(const State &other) const;
  bool operator<(const State &other) const;

  uint64_t value;
  bool is_final;
};

namespace state {
void read(State &state, std::istream &in = std::cin);
void write(const State &state, std::ostream &out = std::cout);
} // namespace state
