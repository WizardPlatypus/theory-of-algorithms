#include "../hpp/rule.hpp"
#include "../hpp/cell.hpp"
#include "../hpp/move.hpp"

bool RuleKey::operator<(const RuleKey &other) const {
  if (this->state == other.state) {
    return this->cell < other.cell;
  }
  return this->state < other.state;
}

bool RuleKey::operator==(const RuleKey &other) const {
  return this->state == other.state && this->cell == other.cell;
}

void RuleKey::read(std::istream &in) {
  state::read(this->state, in);
  cell::read(this->cell, in);
}

void RuleValue::read(std::istream &in) {
  state::read(this->state, in);
  cell::read(this->cell, in);
  move::read(this->move, in);
}

void RuleKey::write(std::ostream &out) const {
  state::write(this->state, out);
  cell::write(this->cell, out);
}

void RuleValue::write(std::ostream &out) const {
  state::write(this->state, out);
  cell::write(this->cell, out);
  move::write(this->move, out);
}
