#include <iostream>
#include "conio.hxx"

Conio::Conio(Color C) {
  code = C;
}
void Conio::setCode(Color C) {
  code = C;
}

std::ostream& operator<<(std::ostream& os, const Conio &f) {
  return os << "\033[38;5;" << f.code << "m";
}

void Conio::clear() {
  std::cout << "\033[2J\033[1;1H" << std::flush;
}

char Conio::getch() {
  char c; // This function should return the keystroke
  system("stty raw");    // Raw input - wait for only a single keystroke
  system("stty -echo");  // Echo off
  std::cin >> c;
  system("stty cooked"); // Cooked input - reset
  system("stty echo");   // Echo on - Reset
  return c;
}
