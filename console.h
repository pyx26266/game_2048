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
//For Formatting Game background
#define BORDER "\t\t\t\t"<<(char)186
#define PIPE <<(char)179<<

enum concol
	{
		black=0,
		dark_blue=1,
		dark_green=2,
		dark_aqua,dark_cyan=3,
		dark_red=4,
		dark_purple=5,dark_pink=5,dark_magenta=5,
		dark_yellow=6,
		dark_white=7,
		gray=8,
		blue=9,
		green=10,
		aqua=11,cyan=11,
		red=12,
		purple=13,pink=13,magenta=13,
		yellow=14,
		white=15
	};
/**Below given some beauty of WIN API
*  To make the game attractive.
*  Give console a name.
*  These code is copied from WIN API documentation as per requirment
*/
HANDLE std_con_out;

inline void textcolor(int color){
SetConsoleTextAttribute(std_con_out,color);
}
void initconsole()
{	
	std_con_out=GetStdHandle(STD_OUTPUT_HANDLE);	
	TCHAR TITLE[10];
	StringCchPrintf(TITLE,10,TEXT("**2048**"));
	SetConsoleTitle(TITLE);
	SetConsoleTextAttribute(std_con_out,white);
}
