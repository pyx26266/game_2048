#include <iostream>
#include "con_color.hxx"

Formatter::Formatter(Color C) {
  code = C;
}
void Formatter::setCode(Color C) {
  code = C;
}

std::ostream& operator<<(std::ostream& os, const Formatter &f) {
  return os << "\033[38;5;" << f.code << "m";
}
