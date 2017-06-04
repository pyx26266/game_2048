
#include <iostream>			//Basic I/O functions
#include <string>			//For toupper() function
#include <stdio.h>
#include <stdlib.h>
#include "game.hxx"			// And this Ofcourse for the game itself
char file_IO::DATA[20] = "file0101";

using namespace std;
int main() {
  bool back_menu(false),
       game_over(false),
       //Just to exclude generating random no. while invalid key is pressed or no movement encountered
       process(true);

  game_2048 game;
  //initconsole();
  do {
    back_menu = false;
    game.intro();
    game_over = false;
    while (game_over == false) {
      Conio::clear();
      if (process == true)
          game.heart();
      game.background();
      game.option = Conio::getch();
      game.option = toupper((char) game.option);
      switch ( game.option ) {
        case KEY_A:
          process = game.move_left();
          break;
        case KEY_D:
          process = game.move_right();
          break;
        case KEY_W:
          process = game.move_up();
          break;
        case KEY_S:
          process = game.move_down();
          break;
        case KEY_ESC:  {
          cout <<"\n\t\tAre you sure to exit?  (y/n)\t";
          char ch = Conio::getch();
          if (ch == KEY_Y || ch == KEY_y) {
            game.store_data(game.ActivePlayer);
            back_menu = true;
            game_over = true;
          }}
          break;
        default:
          game.msgbox(" INVALID INPUT!");
          process = false;
          break;
      }
      if (game.check_win() == GAME_OVER) {
        game.msgbox(" GAME OVER! ", 2);
        back_menu = true;
        game_over = true;
        cout << "Any key to continue...";
        cin.get();
      } else if (game.check_win() == GAME_WIN) {
        game.msgbox(" ** You Win **",2);
        back_menu = true;
        game_over = true;
        cout << "Any key to continue...";
        cin.get();
      }
		
    }
  }while (back_menu == true);
  cout << "Any key to continue...";
  cin.get();
  return 0;	
}
