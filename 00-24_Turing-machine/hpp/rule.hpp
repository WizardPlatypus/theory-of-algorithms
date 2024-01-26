#pragma once
#include "cell.hpp"
#include "move.hpp"
#include <iostream>

struct RuleKey {
  void read(std::istream &in = std::cin);
  void write(std::ostream &out = std::cout) const;

  bool operator==(const RuleKey &other) const;
  bool operator<(const RuleKey &other) const;

  int state;
  bool is_final = false;
  Cell cell;
};

struct RuleValue {
  void read(std::istream &in = std::cin);
  void write(std::ostream &out = std::cout) const;

  int state;
  bool is_final = false;
  Cell cell;
  Move move;
};
