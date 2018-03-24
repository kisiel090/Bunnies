#include<cstdlib>
#include<iostream>
#include<fstream>
#include<vector>
#include "Bunny.h"

std::vector <std::string> Bunny::maleNames;
std::vector <std::string> Bunny::femaleNames;
int board[80][80] = {[0 ... 79][0 ... 79] = -1};

unsigned short getRandomFreeTileDirection(int x, int y, int &board[][])(
    vector<short> freeDirections;
    for(short i =0; i<9; i++)
		freeDirections.push_back(i); //fill 12345///
	for(int i=0; i<3; i++
		for(int j =0; j<3; j++){
			if(board[x+i][y+j]!=0) //if occupied then erase
				freeDirections.erase(freeDirections.begin()+3*x+y);
		}
	if(freeDirections.size()) //if space available
		return freeDirections[rand()%freeDirections.size()];
	return 5;//if no space available then stand still
}

bool Bunny::getNames(std::string filename, bool mf){
    std::fstream input;
    std::string namme;
    input.open(filename.c_str());
    int i=0;
    if(input.is_open()){
        if(mf){
            while(input.good()){
                getline(input, namme);
                Bunny::maleNames.push_back(namme);
                i++;
            }
        }
        else{
            while(input.good()){
                getline(input, namme);
                Bunny::femaleNames.push_back(namme);
                i++;
            }
        }
        input.close();
        return 0;
    }
    else{
        return 1;
    }
}

Bunny::Bunny(colors mothercolor, unsigned short mx, unsigned short my)
{
    sex = rand()%2;
    (double)rand()/RAND_MAX <= 0.02 ? radioactive_mutant_vampire_bunny = true : radioactive_mutant_vampire_bunny = false;
    color = mothercolor;
    age = 0;
    sex ? name = maleNames[rand()%maleNames.size()] : name = femaleNames[rand()%femaleNames.size()];
    if(radioactive_mutant_vampire_bunny)
        name="Darth " + name;
    x=mx;
    y=my;
    getRandomFreeTileDirection(x, y,
}

