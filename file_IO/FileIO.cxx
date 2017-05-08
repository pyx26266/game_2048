#include <iostream>
#include <fstream>				//For file I/O Functions
#include <unistd.h>                             //For usleep
#include <cstdlib>                              //For exit
#include "FileIO.hxx"
using namespace std;
const int MAX_PLAYER = 5;

inline void file_IO::panic(char msg[100]){
    cout<<std::endl<<"\a\t";
    cout<<msg<<std::endl;
        sleep(2);
    exit(EXIT_FAILURE);
}

bool file_IO::check_file(){	
        fin.open(DATA,ios::in);
	if(!fin)
                return false;
	else
        { fin.close();	return true;}
}

void file_IO::store_data(user_data &u){
	
		user_data* temp;
		temp=new user_data[MAX_PLAYER];
        if(check_file()==true)
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
    finout.open(DATA,ios::in |ios::binary);
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
