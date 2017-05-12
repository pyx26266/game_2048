#ifndef CON_COLOR_HXX
#define CON_COLOR_HXX
//Magical numbers to be used throughout the program execution to interact with USER.
#define A 65
#define Y 89
#define y 121
#define D 68
#define W 87
#define S 83
#define ESC 27
#define ZERO 48
#define ONE 49
#define TWO 50
#define THREE 51
#define FOUR 52
#define FIVE 53
#define GAME_OVER 0
#define GAME_WIN 1
#define GAME_CONTINUE -1
const char H_BAR[] = "\u2550";
const char V_BAR[] = "\u2551";
const char L_UP[] = "\u2554";
const char L_BOTTOM[] = "\u255A";
const char R_UP[] = "\u2557";
const char R_BOTTOM[] = "\u255D";
const char T_DOWN[] = "\u2566";
const char T_UP[] = "\u2569";
const char T_LEFT[] = "\u2560";
const char T_RIGHT[] = "\u2563";
const char T_CENTER[] = "\u256C";

enum Color : short int {
  red=1,
  dark_green=2,
  orange=3,
  blue=4,
  yellow=11,
  white=15,
  black=16,
  brown=52,
  gray=245,
  light_blue=62
};
class Formatter {
 public:
  Formatter(Color C);
  
  void setCode(Color C);

  friend std::ostream& operator<<(std::ostream& os, const Formatter &f);

 private:
  Color code;
};
const Formatter defWhite(Color::white);
#endif
