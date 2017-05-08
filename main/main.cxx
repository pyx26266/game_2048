
#include <iostream>			//Basic I/O functions
#include <string>			//For toupper() function
#include <stdio.h>
#include <stdlib.h>
#include "game.hxx"			// And this Ofcourse for the game itself
char file_IO::DATA[20] = "file0101";
char getch()
{
      char c; // This function should return the keystroke
      system("stty raw");    // Raw input - wait for only a single keystroke
      system("stty -echo");  // Echo off
      std::cin >> c;
      system("stty cooked"); // Cooked input - reset
      system("stty echo");   // Echo on - Reset
      return c;
}

using namespace std;
int main()
{	
  bool back_menu=false,game_over=false;
  //Just to exclude generating random no. while invalid key is pressed or no movement encountered
  bool process=true;
  game_2048 game;
  //initconsole();
  do{
    back_menu=false;
    game.intro();
    game_over=false;
    for(;game_over==false;)
    {
      cout << "\033[2J\033[1;1H";
      if(process==true) game.heart();
      game.background();
      //cin.ignore(1000, '\n');
      game.option=getch();
      game.option=toupper((char) game.option);
      switch(game.option){
        case A: 
          process=game.move_left();
          break;
        case D:
          process=game.move_right();
          break;
        case W:
          process=game.move_up();
          break;
        case S:
          process=game.move_down();
          break;
        case ESC:	cout<<"\n\t\tAre you sure to exit?  (y/n)\t";
          char ch;
          ch = getch();
          if(ch==Y||ch==y)
          {
            game.store_data(game.ActivePlayer);
            back_menu=true;
            game_over=true;
          }
          break;
        default:
          game.msgbox(" INVALID INPUT!",1000);
          process=false;
          break;
      }
      if(game.check_win()==GAME_OVER)
      {
        game.msgbox(" GAME OVER! ",100);				
        back_menu=true;
        game_over=true;
        cout << "Any key to continue...";
        cin.get();
      }
      else if(game.check_win()==GAME_WIN)
      {
        game.msgbox(" ** You Win **",1000);
        back_menu=true;
        game_over=true;
        cout << "Any key to continue...";
        cin.get();
      }
		
    }
  }while(back_menu==true);
  cout << "Any key to continue...";
  cin.get();
  return 0;	
}
