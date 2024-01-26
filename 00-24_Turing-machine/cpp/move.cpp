#include "../hpp/move.hpp"
#include <iostream>

namespace move {
void read(Move &move, std::istream &in) {
  char c;
  in >> c;
  if (c == 'L') {
    move = Move::Left;
  } else if (c == 'R') {
    move = Move::Right;
  } else {
    move = Move::None;
  }
}

void write(const Move &move, std::ostream &out) {
  if (move == Move::Left) {
    out << 'L';
  } else if (move == Move::Right) {
    out << 'R';
  }
}
} // namespace move
