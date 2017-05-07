#include <fstream>				//For file I/O Functions
#define DATA "file0101.pix"		//Our file where data wiil be saved
#define MAX_PLAYER 5

using namespace std;
class user_data{
public:
	int id;
	char name[50];
	int high_score;
	int element[4][4];
	user_data(){
		for(int i=0;i<4;++i)
			for(int j=0;j<4;++j)
				element[i][j]=0;
		high_score=0;		
		id=0;
		strcpy(name,"NULL");
	}
};

class file_IO{
private:
void remove_file();
	ifstream fin;
	ofstream fout;
	fstream finout;	
inline void panic(char msg[100]){
	textcolor(red);
	cout<<endl<<"\a\t";
	cout<<msg<<endl;
	Sleep(1500);
	exit(EXIT_FAILURE);
}
protected:
	bool check_file();	//checks if file is on disk or not for initializing saved game data
public:					
	void store_data(user_data &u);
	int read_data(user_data* u);
	void remove_data(user_data &u);
};

bool file_IO::check_file(){	
	fin.open(DATA,ios::in|ios::_Nocreate);
	if(!fin)
		return FALSE;
	else
	{ fin.close();	return TRUE;}	
}

void file_IO::store_data(user_data &u){
	
		user_data* temp;
		temp=new user_data[MAX_PLAYER];
		if(check_file()==TRUE)
			read_data(temp);
		for(int i=0;i<MAX_PLAYER;i++)
			{if(temp[i].id >NULL && temp[i].id==u.id)
				{temp[i]=u;break;}
			else if(temp[i].id==NULL)
				{temp[i]=u;break;}
		}
		fout.open(DATA,ios::out|ios::binary);
		if(fout)
		{	cout<<"\n\t\tStoring Data \n";
		for(int i=0;i<MAX_PLAYER;i++)
			fout.write((char*)&temp[i],sizeof(temp[i]));
		fout.close();
		}
		else
		panic("Failed to write file on disk!");
delete []temp;		
}

int file_IO::read_data(user_data* u){
	signed int count=0;
	finout.open(DATA,ios::in|ios::_Nocreate|ios::binary);
	if(finout)
	{
		cout<<"\n\t\tReading Data \n";
		for(int i=0;i<MAX_PLAYER;i++)
		{
			finout.read((char*)&u[i],sizeof(u[i]));
			if(u[i].id>NULL)
				++count;
		}
		finout.close();
	}
	else
		panic("Failed to read file from disk!");
return count;
}

void file_IO::remove_data(user_data &u){
	cout<<"\n\t\tRemoving Data \n";
	user_data* temp;
		temp=new user_data[MAX_PLAYER];
		read_data(temp);
		for(int i=0;i<MAX_PLAYER;i++)
			{
				if(temp[i].id==u.id)
				{temp[i]=user_data();
				break;
				}
			}
	fout.open(DATA,ios::out|ios::binary);
		if(fout)
		{	cout<<"\n\t\tStoring Data \n";
		for(int i=0;i<MAX_PLAYER;i++)
			fout.write((char*)&temp[i],sizeof(temp[i]));
		fout.close();
		}
}