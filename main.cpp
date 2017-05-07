
#include <iostream>			//Basic I/O functions
#include <Windows.h>		//For WIN APIs'
#include <process.h>		//For exit(0) function
#include <strsafe.h>		//For giving console a name with WIN API
#include <conio.h>			//For getch() function
#include <string>			//For toupper() function
#include "game.h"			// And this Ofcourse for the game itself


//Just for fast compilation
#define WIN32_LEAN_AND_MEAN
#define NOCOMM

using namespace std;
int main()
{	
	bool back_menu=FALSE,game_over=FALSE;
//Just to exclude generating random no. while invalid key is pressed or no movement encountered
	bool process=TRUE;			
	game_2048 game;
	initconsole();	
	do{
	back_menu=FALSE;
	game.intro();
	game_over=FALSE;
	for(;game_over==FALSE;)
	{
		system("cls");
		if(process==TRUE) game.heart();
		game.background();
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
					ch=getch();
					if(ch==Y||ch==y)
						{
							game.store_data(game.ActivePlayer);
							back_menu=TRUE;
							game_over=TRUE;
						}
				break;
			default:
				game.msgbox(" INVALID INPUT!",1000);
				process=FALSE;
				break;
		}
		if(game.check_win()==GAME_OVER)
			{
				game.msgbox(" GAME OVER! ",100);				
				back_menu=TRUE;
				game_over=TRUE;
				system("Pause");
			}
		else if(game.check_win()==GAME_WIN)
		{
			game.msgbox(" ** You Win **",1000);
			back_menu=TRUE;
			game_over=TRUE;
			system("pause");
		}
		
	}
	}while(back_menu==TRUE);
	system("pause");
	return 0;	
}
