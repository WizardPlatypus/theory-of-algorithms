#pragma once
#include <istream>
#include "node.hpp"

enum Move { Left, Right, None };

struct RuleKey {
  void read(std::istream &in);

  bool operator==(const RuleKey &other) const;
  bool operator<(const RuleKey &other) const;

  char state;
  Cell cell;
};

struct RuleValue {
  void read(std::istream &in);

  char state;
  Cell cell;
  Move move;
};
