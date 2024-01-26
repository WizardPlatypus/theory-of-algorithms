#include "../hpp/cell.hpp"
#include <iostream>

namespace cell {
void read(Cell &cell, std::istream &in) {
  char c;
  in >> c;
  if (c == '|') {
    cell = Cell::Stick;
  } else if (c == '#') {
    cell = Cell::Sharp;
  } else {
    cell = Cell::Lambda;
  }
}

void write(const Cell &cell, std::ostream &out) { out << (char)cell; }

} // namespace cell
