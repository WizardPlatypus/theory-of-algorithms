#pragma once
#include <iostream>

enum Move { Left, Right, None };

namespace move {
void read(Move &move, std::istream &in = std::cin);
void write(const Move &move, std::ostream &out = std::cout);
} // namespace move
