#include "rule.hpp"
#include <ostream>

bool RuleKey::operator<(const RuleKey &other) const {
  if (this->state == other.state) {
    return this->symbol < other.symbol;
  }
  return this->state < other.state;
}

bool RuleKey::operator==(const RuleKey &other) const {
  return this->state == other.state && this->symbol == other.symbol;
}

std::istream &operator>>(std::istream &in, Move &move) {
  char c;
  in >> c;
  if (c == 'L') {
    move = Move::Left;
  } else if (c == 'R') {
    move = Move::Right;
  } else {
    move = Move::None;
  }
  return in;
}

std::ostream &operator<<(std::ostream &out, Move &move) {
  char c;
  if (move == Move::Left) {
    c = 'L';
  } else if (move == Move::Right) {
    c = 'R';
  } else {
    c = 'X';
  }
  out << c;
  return out;
}

void RuleKey::read(std::istream &in) { in >> this->state >> this->symbol; }

void RuleValue::read(std::istream &in) {
  in >> this->state >> this->symbol >> this->move;
}
