#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <iomanip>
#include "game.hxx"

Conio color(Color::white);
using namespace std;


void game_2048::resetPlayer(user_data &u){
  for(int i = 0; i < 4; ++i)
    for(int j = 0; j < 4; ++j)
      u.element[i][j] = 0;
  u.high_score = 0;
  u.id = 0;
}

void game_2048::init(user_data &ud){			// initializes previous played game data
  ActivePlayer = ud;
}

void game_2048::msgbox(const char ch[],short time){	//For generating msg During GamePlay
  color.setCode(Color::red);
  cout << color;
  cout << "\a\n\t" << ch << "\n";
  cout << defWhite;
  sleep(time);
}

inline void game_2048::draw(const char ch[],int t){
  while (t--)
    cout << ch;
}
inline bool game_2048::merge(int a,int b,int c,int d){
  ActivePlayer.element[a][b] += ActivePlayer.element[c][d];
  ActivePlayer.element[c][d] = 0;
  ActivePlayer.high_score += ActivePlayer.element[a][b];
  return true;
}

bool game_2048::move_left(){
  bool process(false);
  for (i = 0; i < 4; ++i)
    for (j = 0; j < 4; ++j) {
      //checks if its next element is NON-EMPTY and it is EMPTY
      if (ActivePlayer.element[i][j+1] > 0 && ActivePlayer.element[i][j] == 0 && j < 3) {
        //if yes, copy next element to itself
        ActivePlayer.element[i][j] = ActivePlayer.element[i][j+1];
        //and make next element EMPTY
        ActivePlayer.element[i][j+1] = 0;
        process = 1;
      }
      if (j > 0)							//special purpose to prevent pointing an imagenary element
        // checks if its previous element is EMPTY and it is NON-EMPTY
        if (ActivePlayer.element[i][j-1] == 0 && ActivePlayer.element[i][j] > 0)
          j -= 2;					// if yes, sets loop to two step back (guess why?)
      // checks if previous element is equal to it
        else if (ActivePlayer.element[i][j-1] == ActivePlayer.element[i][j])
          process = merge(i, j-1, i, j);			// if yes, move itself to previous element and add into it
    }
  return process;
}

bool game_2048::move_right(){
  bool process(false);
  for (i = 0; i < 4; ++i)
    for (j = 3; j >= 0; --j) {
      if(ActivePlayer.element[i][j-1] > 0 && ActivePlayer.element[i][j] == 0 && j > 0) {
        ActivePlayer.element[i][j] = ActivePlayer.element[i][j-1];
        ActivePlayer.element[i][j-1] = 0;
        process = 1;
      }
      if (j < 3) {
        if (ActivePlayer.element[i][j+1] == 0 && ActivePlayer.element[i][j] > 0)
            j += 2;
      else if (ActivePlayer.element[i][j+1] == ActivePlayer.element[i][j] && ActivePlayer.element[i][j] > 0)
        merge(i, j+1, i, j);
	}
      else if (ActivePlayer.element[i][j-1] == ActivePlayer.element[i][j] && ActivePlayer.element[i][j] > 0)
        process = merge(i, j, i, j-1);
    }
  return process;
}

bool game_2048::move_up(){
  bool process(false);
  for (j = 0; j < 4; ++j)
    for (i = 0; i < 4; ++i) {
        if (ActivePlayer.element[i+1][j] > 0 && ActivePlayer.element[i][j] == 0 && i < 3) {
            ActivePlayer.element[i][j] = ActivePlayer.element[i+1][j];
            ActivePlayer.element[i+1][j] = 0;
            process = 1;
	  }
    if (i)
      if (ActivePlayer.element[i-1][j] == 0 && ActivePlayer.element[i][j] > 0)
        i -= 2;
      else if (ActivePlayer.element[i-1][j] == ActivePlayer.element[i][j])
        process = merge(i-1, j, i, j);
      }
  return process;
}

bool game_2048::move_down(){
  bool process(false);
  for (j = 0; j < 4; ++j)
    for (i = 3; i >= 0; --i) {
        if (ActivePlayer.element[i-1][j] > 0 && ActivePlayer.element[i][j] == 0 && i > 0) {
            ActivePlayer.element[i][j] = ActivePlayer.element[i-1][j];
            ActivePlayer.element[i-1][j] = 0;
            process = 1;
        }
        if ( i < 3) {
            if (ActivePlayer.element[i+1][j] == 0 && ActivePlayer.element[i][j] > 0)
              i += 2;
            else if (ActivePlayer.element[i+1][j] == ActivePlayer.element[i][j] && ActivePlayer.element[i][j] > 0)
              process = merge(i+1, j, i, j);
        } else if (ActivePlayer.element[i-1][j] == ActivePlayer.element[i][j] && ActivePlayer.element[i][j] > 0)
          process = merge(i, j, i-1, j);
    }
  return process;
}

void game_2048 ::draw_no(int r,int c) {
  if (ActivePlayer.element[r][c] != 0)
    cout << setw(7) << ActivePlayer.element[r][c] << setw(8);
  else
    cout << setw(15);
  /*
    else if(ActivePlayer.element[r][c]==1024)
    {
    cout << Conio(Color::gray);
    cout << "    " << ActivePlayer.element[r][c] << "    ";
    cout << defWhite;
    }
    else if(ActivePlayer.element[r][c]==2048)
    {
    cout << defWhite;
    cout << "    " << ActivePlayer.element[r][c] << "    ";
    cout << defWhite;
    }
    else
    cout << "            ";
  */
}

void game_2048 :: background()
{
  cout << "\tWelcome " << ActivePlayer.name;
  cout << '\n' << '\n' << "\t\t\t\tSCORE : " << ActivePlayer.high_score  << '\n';
  cout << "\t"; draw(L_UP, 1); draw(H_BAR,12);cout << T_DOWN; draw(H_BAR,12); cout << T_DOWN;draw(H_BAR,12);cout << T_DOWN;draw(H_BAR,12);cout << R_UP;
  cout << "\n\t" << V_BAR << "\t     " << V_BAR <<"\t\t  " << V_BAR << "\t\t\b" << V_BAR << "\t    " << V_BAR;
  cout << "\n\t" << V_BAR << "\t     " << V_BAR <<"\t\t  " << V_BAR << "\t\t\b" << V_BAR << "\t    " << V_BAR;
  cout << "\n\t" << V_BAR; draw_no(0,0); cout << V_BAR; draw_no(0,1); cout << V_BAR; draw_no(0,2); cout << V_BAR; draw_no(0,3); cout << V_BAR;
  cout << "\n\t" << V_BAR << "\t     " << V_BAR <<"\t\t  " << V_BAR << "\t\t\b" << V_BAR << "\t    " << V_BAR;
  cout << "\n\t" << V_BAR << "\t     " << V_BAR <<"\t\t  " << V_BAR << "\t\t\b" << V_BAR << "\t    " << V_BAR;
  cout << "\n\t" << T_LEFT;draw(H_BAR, 12);cout << T_CENTER;draw(H_BAR, 12);cout << T_CENTER;draw(H_BAR, 12);cout << T_CENTER;draw(H_BAR, 12);cout << T_RIGHT;
  cout << "\n\t" << V_BAR << "\t     " << V_BAR <<"\t\t  " << V_BAR << "\t\t\b" << V_BAR << "\t    " << V_BAR;
  cout << "\n\t" << V_BAR << "\t     " << V_BAR <<"\t\t  " << V_BAR << "\t\t\b" << V_BAR << "\t    " << V_BAR;
  cout << "\n\t" << V_BAR; draw_no(1,0); cout << V_BAR; draw_no(1,1); cout << V_BAR; draw_no(1,2); cout << V_BAR; draw_no(1,3); cout << V_BAR;
  cout << "\n\t" << V_BAR << "\t     " << V_BAR <<"\t\t  " << V_BAR << "\t\t\b" << V_BAR << "\t    " << V_BAR;
  cout << "\n\t" << V_BAR << "\t     " << V_BAR <<"\t\t  " << V_BAR << "\t\t\b" << V_BAR << "\t    " << V_BAR;
  cout << "\n\t" << T_LEFT;draw(H_BAR, 12);cout << T_CENTER;draw(H_BAR, 12);cout << T_CENTER;draw(H_BAR, 12);cout << T_CENTER;draw(H_BAR, 12);cout << T_RIGHT;
  cout << "\n\t" << V_BAR << "\t     " << V_BAR <<"\t\t  " << V_BAR << "\t\t\b" << V_BAR << "\t    " << V_BAR;
  cout << "\n\t" << V_BAR << "\t     " << V_BAR <<"\t\t  " << V_BAR << "\t\t\b" << V_BAR << "\t    " << V_BAR;
  cout << "\n\t" << V_BAR; draw_no(2,0); cout << V_BAR; draw_no(2,1); cout << V_BAR; draw_no(2,2); cout << V_BAR; draw_no(2,3); cout << V_BAR;
  cout << "\n\t" << V_BAR << "\t     " << V_BAR <<"\t\t  " << V_BAR << "\t\t\b" << V_BAR << "\t    " << V_BAR;
  cout << "\n\t" << V_BAR << "\t     " << V_BAR <<"\t\t  " << V_BAR << "\t\t\b" << V_BAR << "\t    " << V_BAR;
  cout << "\n\t" << T_LEFT;draw(H_BAR, 12);cout << T_CENTER;draw(H_BAR, 12);cout << T_CENTER;draw(H_BAR, 12);cout << T_CENTER;draw(H_BAR, 12);cout << T_RIGHT;
  cout << "\n\t" << V_BAR << "\t     " << V_BAR <<"\t\t  " << V_BAR << "\t\t\b" << V_BAR << "\t    " << V_BAR;
  cout << "\n\t" << V_BAR << "\t     " << V_BAR <<"\t\t  " << V_BAR << "\t\t\b" << V_BAR << "\t    " << V_BAR;
  cout << "\n\t" << V_BAR; draw_no(3,0); cout << V_BAR; draw_no(3,1); cout << V_BAR; draw_no(3,2); cout << V_BAR; draw_no(3,3); cout << V_BAR;
  cout << "\n\t" << V_BAR << "\t     " << V_BAR <<"\t\t  " << V_BAR << "\t\t\b" << V_BAR << "\t    " << V_BAR;
  cout << "\n\t" << V_BAR << "\t     " << V_BAR <<"\t\t  " << V_BAR << "\t\t\b" << V_BAR << "\t    " << V_BAR;
  cout << "\n\t" << L_BOTTOM; draw(H_BAR, 12); cout << T_UP; draw(H_BAR, 12); cout << T_UP; draw(H_BAR, 12);
  cout << T_UP; draw(H_BAR, 12); cout << R_BOTTOM;
}

void game_2048::intro(){
  char c;
  user_data* p;
  p = new user_data[5];
  if (check_file() == 1)
    TotalPlayer=read_data(p);
  else
    TotalPlayer = 0;
  do {

    cout << "\033[2J\033[1;1H";
    cout << "\n\t";draw(L_UP,1);draw(H_BAR,47);draw(R_UP,1);
    cout << "\n\t"; draw(V_BAR,1);
    cout << "\tWelcome to the puzzle game " << "`2048`\t"; draw(V_BAR,1);
    cout << "\n\t"; draw(V_BAR, 1); draw("\t", 6); draw(V_BAR, 1);
    if (check_file() == 1) {
      cout << "\n\t"; draw(V_BAR, 1); cout << "\t\t0. Continue\t\t\t" ; draw(V_BAR, 1);
    }
    cout << "\n\t" ; draw(V_BAR, 1); draw("\t", 6); draw(V_BAR, 1);
    cout << "\n\t" ; draw(V_BAR, 1); cout << "\t\t1. New Game\t\t\t" ; draw(V_BAR, 1);
    cout << "\n\t" ; draw(V_BAR, 1); draw("\t", 6); draw(V_BAR, 1);
    cout << "\n\t" ; draw(V_BAR, 1); cout << "\t\t2. Instructions\t\t\t"; draw(V_BAR, 1);
    cout << "\n\t" << V_BAR << "\t\t\t\t\t\t" << V_BAR;
    cout << "\n\t" ; draw(V_BAR, 1); cout << "\t\t3. Remove Player(s)\t\t"; draw(V_BAR, 1);
    cout << "\n\t" << V_BAR << "\t\t\t\t\t\t" << V_BAR;
    cout << "\n\t" ; draw(V_BAR, 1); cout << "\t\t4. EXIT\t\t\t\t" ; draw(V_BAR, 1);
    cout << "\n\t" << V_BAR << "\t\t\t\t\t\t" << V_BAR;
    cout << "\n\t" << V_BAR << "\t\t\t\t\t\t" << V_BAR;
    cout << "\n\t" << L_BOTTOM; draw(H_BAR,47); draw(R_BOTTOM,1);

    cout << "\nAny time hit " << (char)96 << "Esc" << (char)39 << " to exit.\n";
    option = Conio::getch();
    switch ( option ) {
        case KEY_ZERO:  do {
                            Conio::clear();
                            cout << "Id \t Name \t\tHigh Score\n";
                                 draw(H_BAR,35);cout << '\n';
                            for (int i = 0; i < TotalPlayer; ++i)
                              cout << (p+i)->id << "\t" << (p+i)->name << "\t\t " << (p+i)->high_score << '\n';

                            c = Conio::getch();
                            if (p[c - '1'].id)
                                init(p[c - '1']);
                            else
                                msgbox("Invalid Input!"), option = 1;
                           } while(option == 1);
                        break;
        case KEY_ONE:	Conio::clear();
                        if (TotalPlayer < 5) {
                          cout << "Enter Name ";
                          cin >> ActivePlayer.name;
                          resetPlayer(ActivePlayer);
                          ActivePlayer.id=++TotalPlayer;
                        } else
                            msgbox("Maximum Player Present. Delete some Player!",2), option = 0;
                        break;
    case KEY_TWO:	cout << "\033[2J\033[1;1H";
      instructions();
      option=0;
      break;
    case KEY_FOUR:
    case KEY_ESC: exit(0);
      break;
    case KEY_THREE:

      do{
	if(TotalPlayer==0)
          {msgbox("No Saved Game!");option=0;remove(DATA);break;}
	cout << "\033[2J\033[1;1H";
	cout << "Id \t Name \t\tHigh Score\n";
	draw(H_BAR,35);cout << '\n';
	cout << '\n';

	for(int i=0;i<TotalPlayer;++i)
	  cout << (p+i)->id << "\t" << (p+i)->name << "\t\t " << (p+i)->high_score << '\n';
	c=cin.get();
	switch(c){
	case KEY_ONE:
	  if(p[0].id>0)
	    {RemovePlayer(p[0]);option=1;}
	  else
	    {msgbox("Invalid Input!");option=1;}
	  break;
	case KEY_TWO:
	  if(p[1].id>0)
	    {RemovePlayer(p[1]);option=1;}
	  else
	    {msgbox("Invalid Input!");option=1;}
	  break;
	case KEY_THREE:
	  if(p[2].id>0)
	    {RemovePlayer(p[2]);option=1;}
	  else
	    {msgbox("Invalid Input!");option=1;}
	  break;
	case KEY_FOUR:
	  if(p[3].id>0)
	    {RemovePlayer(p[3]);option=1;}
	  else
	    {msgbox("Invalid Input!");option=1;}
	  break;
	case KEY_FIVE:
	  if(p[4].id>0)
	    {RemovePlayer(p[4]);option=1;}
	  else
	    {msgbox("Invalid Input!");option=1;}
	  break;
	case KEY_ESC:
	  option=0;
	  break;
	default:
	  msgbox("Invalid Input!",1000);
	  break;
	}
      }while(option==1);
      break;
    default: option=0;
      msgbox(" Input Error! ",1);
      break;
    }
  }while(option==0);
  delete []p;
}

void game_2048::heart(){
  int rnum1,rnum2,T=0;					// 'T' is created to prevent program to go in infinite loop
  srand(time(0));

  do
    {
      rnum1 = rand()%4,rnum2=rand()%4;			//generates two random no.
      //checks the element pointed by the no. is 0 or not.
      if(ActivePlayer.element[rnum1][rnum2]==0)
	{ActivePlayer.element[rnum1][rnum2]=2;}				// if yes, assign '2' to it
      ++T;
      if(T>49)
	break;
    }while(ActivePlayer.element[rnum1][rnum2]!=2);			//if not, loop continues

}

int game_2048::check_win(){
  /*check if it and its next adjacent element is equal or not or it is equal to '0',
   *if yes, the game is not over,
   *else, game is over
   */
  int status=GAME_OVER;
  for(i=0;i<4;++i)
    for(j=0;j<4;++j)
      {
	if(j<3 && i<3)
	  {if((ActivePlayer.element[i][j]==ActivePlayer.element[i][j+1] || ActivePlayer.element[i][j]==ActivePlayer.element[i+1][j]) || ActivePlayer.element[i][j]==0) status=GAME_CONTINUE;}
	else if(j<4 && i<3)
	  {if(ActivePlayer.element[i][j]==ActivePlayer.element[i+1][j] || ActivePlayer.element[i][j]==0) status=GAME_CONTINUE;}
	else if(j<3)
	  {if(ActivePlayer.element[i][j]==ActivePlayer.element[i][j+1] || ActivePlayer.element[i][j]==0) status=GAME_CONTINUE;}
	if(ActivePlayer.element[i][j]==2048)
	  {status=GAME_WIN; break;}
      }
  return status;
}

void game_2048::instructions(){
  cout << "\nControls :\n\n\t " << "\t  W\tup" << '\n';
  cout << "\t" << "\tA  D left  right" << '\n';
  cout << "\t " << "\t  S\tdown" << '\n';
  cout << "any key to continue...";
  cin.get();
}

void game_2048::RemovePlayer(user_data &u){

  remove_data(u);
  --TotalPlayer;

  cout << '\n';
  cout << "any key to continue...";
  cin.get();
}
