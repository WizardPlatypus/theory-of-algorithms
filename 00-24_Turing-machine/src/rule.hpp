#pragma once
#include <istream>

enum Move { Left, Right, None };

struct RuleKey {
  void read(std::istream &in);

  bool operator==(const RuleKey &other) const;
  bool operator<(const RuleKey &other) const;

  char state;
  char symbol;
};

struct RuleValue {
  void read(std::istream &in);

  char state;
  char symbol;
  Move move;
};
