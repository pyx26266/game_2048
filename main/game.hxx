#ifndef GAME_HXX
#define GAME_HXX
#include <iostream>
#include <fstream>
#include <conio/conio.hxx>
#include <file_IO/FileIO.hxx>

class game_2048: public file_IO {
    int i, j;
    inline bool merge(int, int, int, int);
    inline void draw (const char [], int t);
public:
    int TotalPlayer;
    user_data ActivePlayer;
    int option;
    void intro();
    void instructions();
    void draw_no(int, int);
    void msgbox(const char ch[], short time = 1 );
    void init(user_data &ud);
    void resetPlayer(user_data &u);
    void background();
    void heart();
    int check_win();
    void RemovePlayer(user_data &u);
    bool move_left();
    bool move_right();
    bool move_up();
    bool move_down();
};

#endif
