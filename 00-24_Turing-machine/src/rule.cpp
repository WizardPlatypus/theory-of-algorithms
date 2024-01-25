#include "rule.hpp"

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

void RuleKey::read(std::istream &in) { in >> this->state >> this->symbol; }

void RuleValue::read(std::istream &in) {
  in >> this->state >> this->symbol >> this->move;
}
