#ifndef FileIO_HXX
#define FileIO_HXX
class user_data{
public:
	unsigned int id;
    char name[20];
	unsigned int high_score;
	unsigned int element[4][4];
	user_data(){
        element[4][4] = {0};
		high_score = 0;
		id = 0;
	}
};

class file_IO{
private:
	void remove_file();
    std::ifstream fin;
    std::ofstream fout;
    std::fstream finout;
    inline void panic(char msg[100]);
protected:
	bool check_file();	//checks if file is on disk or not for initializing saved game data
public:
        static char DATA[20];
	void store_data(user_data &u);
	int read_data(user_data* u);
	void remove_data(user_data &u);
};


#endif
