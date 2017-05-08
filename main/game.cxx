#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "game.hxx"

Formatter color(Color::white);
using namespace std;


void game_2048::resetPlayer(user_data &u){
        for(int i=0;i<4;++i)
        for(int j=0;j<4;++j)
                u.element[i][j]=0;
u.high_score=0;
u.id=0;
}

void game_2048::init(user_data &ud){			// initializes previous played game data
        ActivePlayer=ud;
}

void game_2048::msgbox(char ch[80],int time){	//For generating msg During GamePlay
        color.setCode(Color::red);
        cout << color;
        cout<<"\a\n\t"<<ch<<"\n";
        cout << defWhite;
        sleep(time);
}

void game_2048::draw(int n,int t){
    for(i=0;i<t;++i)
        cout<<(char)n;
}
inline bool game_2048::merge(int a,int b,int c,int d){
        ActivePlayer.element[a][b]+=ActivePlayer.element[c][d];
        ActivePlayer.element[c][d]=0;
        ActivePlayer.high_score+=ActivePlayer.element[a][b];
        return true;
        }

bool game_2048::move_left(){
bool process=false;
        for(i=0;i<4;++i)
                for(j=0;j<4;++j)
                {		//checks if its next element is NON-EMPTY and it is EMPTY
                        if(ActivePlayer.element[i][j+1]>0 && ActivePlayer.element[i][j]==0 && j<3)
                        {		//if yes, copy next element to itself
                                ActivePlayer.element[i][j]=ActivePlayer.element[i][j+1];
                                        //and make next element EMPTY
                                ActivePlayer.element[i][j+1]=0;
                                process=1;
                        }
                        if(j>0)							//special purpose to prevent pointing an imagenary element
                                // checks if its previous element is EMPTY and it is NON-EMPTY
                                if(ActivePlayer.element[i][j-1]==0 && ActivePlayer.element[i][j]>0)
                                        j-=2;					// if yes, sets loop to two step back (guess why?)
                                // checks if previous element is equal to it
                                else if(ActivePlayer.element[i][j-1]==ActivePlayer.element[i][j])
                                        process=merge(i,j-1,i,j);			// if yes, move itself to previous element and add into it
                }

return process;
}

bool game_2048::move_right(){
bool process=0;
        for(i=0;i<4;++i)
                for(j=3;j>=0;--j)
                {
                        if(ActivePlayer.element[i][j-1]>0 && ActivePlayer.element[i][j]==0 && j>0)
                        {
                                ActivePlayer.element[i][j]=ActivePlayer.element[i][j-1];
                                ActivePlayer.element[i][j-1]=0;
                                process=1;
                        }
                        if(j<3)
                                {if(ActivePlayer.element[i][j+1]==0 && ActivePlayer.element[i][j]>0)
                                        j+=2;
                                else if(ActivePlayer.element[i][j+1]==ActivePlayer.element[i][j] && ActivePlayer.element[i][j]>0)
                                        merge(i,j+1,i,j);
                        }
                        else if(ActivePlayer.element[i][j-1]==ActivePlayer.element[i][j] && ActivePlayer.element[i][j]>0)
                                        process=merge(i,j,i,j-1);
                }
                return process;
}

bool game_2048::move_up(){
        bool process=0;
        for(j=0;j<4;++j)
                for(i=0;i<4;++i)
                {
                        if(ActivePlayer.element[i+1][j]>0 && ActivePlayer.element[i][j]==0 && i<3)
                        {
                                ActivePlayer.element[i][j]=ActivePlayer.element[i+1][j];
                                ActivePlayer.element[i+1][j]=0;
                                process=1;
                        }
                        if(i>0)
                                if(ActivePlayer.element[i-1][j]==0 && ActivePlayer.element[i][j]>0)
                                        i-=2;
                                else if(ActivePlayer.element[i-1][j]==ActivePlayer.element[i][j])
                                        process=merge(i-1,j,i,j);
                }
                return process;
}

bool game_2048::move_down(){
        bool process=0;
        for(j=0;j<4;++j)
                for(i=3;i>=0;--i)
                {
                        if(ActivePlayer.element[i-1][j]>0 && ActivePlayer.element[i][j]==0 && i>0)
                        {
                                ActivePlayer.element[i][j]=ActivePlayer.element[i-1][j];
                                ActivePlayer.element[i-1][j]=0;
                                process=1;
                        }
                        if(i<3)
                                {if(ActivePlayer.element[i+1][j]==0 && ActivePlayer.element[i][j]>0)
                                        i+=2;
                                else if(ActivePlayer.element[i+1][j]==ActivePlayer.element[i][j] && ActivePlayer.element[i][j]>0)
                                        process=merge(i+1,j,i,j);
                        }
                        else if(ActivePlayer.element[i-1][j]==ActivePlayer.element[i][j] && ActivePlayer.element[i][j]>0)
                                        process=merge(i,j,i-1,j);
                }
                return process;
}

void game_2048 ::draw_no(int r,int c)
{	if(ActivePlayer.element[r][c]==2)
        {

                color.setCode(Color::gray);
                cout << color;
                cout<<"     "<<ActivePlayer.element[r][c]<<"      ";
                cout << defWhite;
        }
        else if(ActivePlayer.element[r][c]==4)
        {
                cout << Formatter(Color::blue);
                cout<<"     "<<ActivePlayer.element[r][c]<<"      ";
                cout << defWhite;
        }
        else if(ActivePlayer.element[r][c]==8)
        {
                cout << Formatter(Color::yellow);
                cout<<"     "<<ActivePlayer.element[r][c]<<"      ";
                cout << defWhite;
        }
        else if(ActivePlayer.element[r][c]==16)
        {
                cout << Formatter(Color::brown);
                cout<<"    "<<ActivePlayer.element[r][c]<<"      ";
                cout << defWhite;
        }
        else if(ActivePlayer.element[r][c]==32)
        {
                cout<<"    "<<ActivePlayer.element[r][c]<<"      ";
                cout << defWhite;
        }
        else if(ActivePlayer.element[r][c]==64)
        {
                cout << Formatter(Color::red);
                cout<<"    "<<ActivePlayer.element[r][c]<<"      ";
                cout << defWhite;
        }
        else if(ActivePlayer.element[r][c]==128)
        {
                cout << Formatter(Color::yellow);
                cout<<"    "<<ActivePlayer.element[r][c]<<"     ";
                cout << defWhite;
        }
        else if(ActivePlayer.element[r][c]==256)
        {
                cout<<"    "<<ActivePlayer.element[r][c]<<"     ";
        }
        else if(ActivePlayer.element[r][c]==512)
        {
                cout << Formatter(Color::dark_green);
                cout<<"    "<<ActivePlayer.element[r][c]<<"     ";
                cout << defWhite;
        }
        else if(ActivePlayer.element[r][c]==1024)
        {
                cout << Formatter(Color::gray);
                cout<<"    "<<ActivePlayer.element[r][c]<<"    ";
                cout << defWhite;
        }
        else if(ActivePlayer.element[r][c]==2048)
        {
                cout << defWhite;
                cout<<"    "<<ActivePlayer.element[r][c]<<"    ";
                cout << defWhite;
        }
                else
                        cout<<"            ";
}

void game_2048 :: background()
{
        cout<<"\tWelcome "<<ActivePlayer.name;
        cout<<endl<<endl<<"\t\t\t\tSCORE :"<<ActivePlayer.high_score <<endl;
        cout<<"\t"<<(char)218;draw(196,12);cout<<(char)194;draw(196,12);cout<<(char)194;draw(196,12);cout<<(char)194;draw(196,12);cout<<(char)191<<endl;
        cout<<"\t"PIPE"            "PIPE"            "PIPE"            "PIPE"            "PIPE"\n";
        cout<<"\t"PIPE"            "PIPE"            "PIPE"            "PIPE"            "PIPE"\n";
        cout<<"\t"<<(char)179;draw_no(0,0);cout<<(char)179;draw_no(0,1);cout<<(char)179;draw_no(0,2);cout<<(char)179;draw_no(0,3);cout PIPE"\n";
        cout<<"\t"PIPE"            "PIPE"            "PIPE"            "PIPE"            "PIPE"\n";
        cout<<"\t"<<(char)195;draw(196,12);cout<<(char)197;draw(196,12);cout<<(char)197;draw(196,12);cout<<(char)197;draw(196,12);cout<<(char)180<<"\n";
        cout<<"\t"PIPE"            "PIPE"            "PIPE"            "PIPE"            "PIPE"\n";
        cout<<"\t"PIPE"            "PIPE"            "PIPE"            "PIPE"            "PIPE"\n";
        cout<<"\t"<<(char)179;draw_no(1,0);cout<<(char)179;draw_no(1,1);cout<<(char)179;draw_no(1,2);cout<<(char)179;draw_no(1,3);cout PIPE"\n";
        cout<<"\t"PIPE"            "PIPE"            "PIPE"            "PIPE"            "PIPE"\n";
        cout<<"\t"<<(char)195;draw(196,12);cout<<(char)197;draw(196,12);cout<<(char)197;draw(196,12);cout<<(char)197;draw(196,12);cout<<(char)180<<"\n";
        cout<<"\t"PIPE"            "PIPE"            "PIPE"            "PIPE"            "PIPE"\n";
        cout<<"\t"PIPE"            "PIPE"            "PIPE"            "PIPE"            "PIPE"\n";
        cout<<"\t"<<(char)179;draw_no(2,0);cout<<(char)179;draw_no(2,1);cout<<(char)179;draw_no(2,2);cout<<(char)179;draw_no(2,3);cout PIPE"\n";
        cout<<"\t"PIPE"            "PIPE"            "PIPE"            "PIPE"            "PIPE"\n";
        cout<<"\t"<<(char)195;draw(196,12);cout<<(char)197;draw(196,12);cout<<(char)197;draw(196,12);cout<<(char)197;draw(196,12);cout<<(char)180<<"\n";
        cout<<"\t"PIPE"            "PIPE"            "PIPE"            "PIPE"            "PIPE"\n";
        cout<<"\t"PIPE"            "PIPE"            "PIPE"            "PIPE"            "PIPE"\n";
        cout<<"\t"<<(char)179;draw_no(3,0);cout<<(char)179;draw_no(3,1);cout<<(char)179;draw_no(3,2);cout<<(char)179;draw_no(3,3);cout PIPE"\n";
        cout<<"\t"PIPE"            "PIPE"            "PIPE"            "PIPE"            "PIPE"\n";
        cout<<"\t"<<(char)192;draw(196,12);cout<<(char)193;draw(196,12);cout<<(char)193;draw(196,12);cout<<(char)193;draw(196,12);cout<<(char)217<<"\n";
}

void game_2048::intro(){
        int c;
        user_data* p;
                p=new user_data[5];
                if(check_file()==1)
                                        TotalPlayer=read_data(p);
                                else
                                        TotalPlayer=0;
do{

        cout << "\033[2J\033[1;1H";
        cout<<"\n\t";draw(201,1);draw(205,47);draw(187,1);
        cout<<"\n\t"<<(char)186<<"\t\t"<<BORDER<<"\n\t"<<(char)186;
        cout<<"\tWelcome to the puzzle game "<<(char)96<<"2048'\t"<<(char)186<<"\n\t"<<(char)186<<"\t\t"<<BORDER;
                if(check_file()==1)
                        cout<<"\n\t"<<(char)186<<"\t\t0. Continue\t\t\t"<<(char)186<<"\n\t"<<(char)186<<"\t\t"<<BORDER;
                cout<<"\n\t"<<(char)186<<"\t\t1. New Game\t\t\t"<<(char)186<<"\n\t"<<(char)186<<"\t\t"<<BORDER;
                cout<<"\n\t"<<(char)186<<"\t\t2. Instructions"<<"\t\t\t"<<(char)186<<"\n\t"<<(char)186<<"\t\t"<<BORDER;
                cout<<"\n\t"<<(char)186<<"\t\t3. Remove Player(s)"<<"\t\t"<<(char)186<<"\n\t"<<(char)186<<"\t\t"<<BORDER;
                cout<<"\n\t"<<(char)186<<"\t\t4. EXIT"<<BORDER<<"\n\t"<<(char)186<<"\t\t"<<BORDER;
                cout<<endl<<"\t"<<(char)186<<"\t\t"<<BORDER<<endl;
                cout<<"\t"<<(char)186<<"\t\t"<<BORDER<<endl;
                cout<<"\t"<<(char)186<<"\t\t"<<BORDER<<endl;
                cout<<"\t"<<(char)200;draw(205,47);cout<<(char)188<<endl;

                cout<<"\nAny time hit "<<(char)96<<"Esc"<<(char)39<<" to exit.\n";
                option=cin.get();
        switch(option){
                case ZERO:
                                do{
                                        cout << "\033[2J\033[1;1H";
                                        cout<<"Id \t Name \t\tHigh Score\n";
                                        draw(196,35);cout<<endl;
                                        for(int i=0;i<TotalPlayer;++i)
                                        cout<<(p+i)->id<<"\t"<<(p+i)->name<<"\t\t "<<(p+i)->high_score<<endl;
                                        c=cin.get();
                                        switch(c){
                                        case ONE:
                                                if(p[0].id>0)
                                                        init(p[0]);
                                                else
                                                        {msgbox("Invalid Input!");option=1;}
                                                break;
                                        case TWO:
                                                if(p[1].id>0)
                                                        init(p[1]);
                                                else
                                                        {msgbox("Invalid Input!");option=1;}
                                                break;
                                        case THREE:
                                                if(p[2].id>0)
                                                        init(p[2]);
                                                else
                                                        {msgbox("Invalid Input!");option=1;}
                                                break;
                                        case FOUR:
                                                if(p[3].id>0)
                                                        init(p[3]);
                                                else
                                                        {msgbox("Invalid Input!");option=1;}
                                                break;
                                        case FIVE:
                                                if(p[4].id>0)
                                                        init(p[4]);
                                                else
                                                        {msgbox("Invalid Input!");option=1;}
                                                break;
                                        case ESC:
                                                option=0;
                                                break;
                                        default:
                                                msgbox("Invalid Input!",1000);
                                                option=1;
                                                break;
                                        }
                                }while(option==1);
                                break;
                case ONE:	cout << "\033[2J\033[1;1H";

                                if(TotalPlayer<5)
                                {
                                cout<<"Enter Name ";
                                cin>>ActivePlayer.name;
                                resetPlayer(ActivePlayer);
                                ActivePlayer.id=++TotalPlayer;
                                }
                                else
                                {msgbox("Maximum Player Present. Delete some Player!",1500);option=0;}
                                break;
                case TWO:	cout << "\033[2J\033[1;1H";
                                        instructions();
                                        option=0;
                                break;
                case FOUR:
                case ESC: exit(0);
                                break;
                case THREE:

                                do{
                                        if(TotalPlayer==0)
                                {msgbox("No Saved Game!");option=0;remove(DATA);break;}
                        cout << "\033[2J\033[1;1H";
                        cout<<"Id \t Name \t\tHigh Score\n";
                        draw(196,35);cout<<endl;
                        cout<<endl;

                                for(int i=0;i<TotalPlayer;++i)
                                        cout<<(p+i)->id<<"\t"<<(p+i)->name<<"\t\t "<<(p+i)->high_score<<endl;
                                c=cin.get();
                        switch(c){
                                        case ONE:
                                                if(p[0].id>0)
                                                        {RemovePlayer(p[0]);option=1;}
                                                else
                                                        {msgbox("Invalid Input!");option=1;}
                                                break;
                                        case TWO:
                                                if(p[1].id>0)
                                                        {RemovePlayer(p[1]);option=1;}
                                                else
                                                        {msgbox("Invalid Input!");option=1;}
                                                break;
                                        case THREE:
                                                if(p[2].id>0)
                                                        {RemovePlayer(p[2]);option=1;}
                                                else
                                                        {msgbox("Invalid Input!");option=1;}
                                                break;
                                        case FOUR:
                                                if(p[3].id>0)
                                                        {RemovePlayer(p[3]);option=1;}
                                                else
                                                        {msgbox("Invalid Input!");option=1;}
                                                break;
                                        case FIVE:
                                                if(p[4].id>0)
                                                        {RemovePlayer(p[4]);option=1;}
                                                else
                                                        {msgbox("Invalid Input!");option=1;}
                                                break;
                                        case ESC:
                                                option=0;
                                                break;
                                        default:
                                                msgbox("Invalid Input!",1000);
                                                break;
                                        }
                                }while(option==1);
                                break;
                default: option=0;
                                msgbox(" Input Error! ",500);
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
        cout<<"\nControls :\n\n\t "<<(char)30<<"    W"<<endl;
                cout<<"\t"<<(char)17<<" "<<(char)16<<"  A D"<<endl;
                cout<<"\t "<<(char)31<<"    S"<<endl;
                cout << "any key to continue...";
                cin.get();
}

void game_2048::RemovePlayer(user_data &u){

        remove_data(u);
        --TotalPlayer;

        cout<<endl;
        cout << "any key to continue...";
        cin.get();
}
