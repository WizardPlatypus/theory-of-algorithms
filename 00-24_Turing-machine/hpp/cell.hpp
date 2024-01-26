#pragma once
#include <iostream>

// | # -
enum Cell { Stick = '|', Sharp = '#', Lambda = 'A' };

namespace cell {
void read(Cell &cell, std::istream &in = std::cin);
void write(const Cell &cell, std::ostream &out = std::cout);
} // namespace cell
