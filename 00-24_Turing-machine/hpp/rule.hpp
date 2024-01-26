#pragma once
#include "cell.hpp"
#include "move.hpp"
#include "state.hpp"
#include <iostream>

struct RuleKey {
  void read(std::istream &in = std::cin);
  void write(std::ostream &out = std::cout) const;

  bool operator==(const RuleKey &other) const;
  bool operator<(const RuleKey &other) const;

  State state;
  Cell cell;
};

struct RuleValue {
  void read(std::istream &in = std::cin);
  void write(std::ostream &out = std::cout) const;

  State state;
  Cell cell;
  Move move;
};
