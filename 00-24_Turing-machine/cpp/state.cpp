#include "../hpp/state.hpp"
#include <iostream>

bool State::operator==(const State &other) const {
  return this->is_final == other.is_final && this->value == other.value;
}

bool State::operator<(const State &other) const {
  if (other.is_final) {
    return true;
  }
  if (this->is_final) {
    return false;
  }
  return this->value < other.value;
}

namespace state {
void read(State &state, std::istream &in) {
  std::string s;
  in >> s;
  if (s == "*") {
    state.is_final = true;
    state.value = 0;
  } else {
    state.is_final = false;
    state.value = std::stoi(s);
  }
}

void write(const State &state, std::ostream &out) {
  out << 'q';
  if (state.is_final) {
    out << '*';
  } else {
    out << state.value;
  }
}
} // namespace state
