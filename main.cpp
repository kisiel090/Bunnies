#include<iostream>
#include<time.h>
#include<cstdlib>

#include<vector>
#include<iomanip>
#include<fstream>

#include<thread>
#include<chrono>
#include<cmath>

#include<windows.h>


#include"Bunny.h"

using namespace std;

void FYShuffle(int sizee, int* address){
    int tab[sizee];
    int j, buf;
    for(int i=0; i<sizee; i++){
        tab[i]=i;
    }
    for(int i=0; i<sizee-2; i++){
        j=rand()%(sizee-i-1)+i;
        buf=tab[j];
        tab[j]=tab[i];
        tab[i]=buf;
    }
    for(int i=0; i<sizee; i++){
        address[i]=tab[i];
    }
}

void printBunnyTable(vector<Bunny> &bunnies, unsigned short &males, unsigned short &females, vector<int> &normalBunnies, vector<colors> &mothercolors, ostream &out, Bunny &newborn){
    out<<"|age| name            |S|C|V |\n";
    out<<"------------------------------\n";
    for(unsigned int i=0; i<bunnies.size(); i++){
        // |  9|fjbaf sadfasdf   |1|2|0 |
        out<<"||"<<setw(2)<<bunnies[i].age<<"|"<<setw(17)<<bunnies[i].name<<"|"<<setw(1)<<bunnies[i].sex<<"|"<<setw(1)<<bunnies[i].color<<"|"<<setw(1)<<bunnies[i].radioactive_mutant_vampire_bunny<<"||\n";

        bunnies[i].age++;
        if(bunnies[i].radioactive_mutant_vampire_bunny == false){
            normalBunnies.push_back(i); //needed later for vampires spread
            if(bunnies[i].age>2){
                if(bunnies[i].sex){
                    males++;
                }
                else{
                    females++;
                    mothercolors.push_back( bunnies[i].color); //childrens are born with mother color
                }
            }
        }
    }
    out<<"------------------------------\n";
}
void vampireSpread(vector<Bunny> &bunnies, vector<int> &normalBunnies, ostream &out, Bunny &newborn){
    unsigned int darthPool = bunnies.size()-normalBunnies.size();
    if(darthPool!=0 && normalBunnies.size()!=0){
        int* ids= new int[normalBunnies.size()];
        FYShuffle(normalBunnies.size(), ids);
        out<<"Radioactive mutant vampire bunnies are spreading...\n";
        for(unsigned int i = 0; i<darthPool && i<normalBunnies.size(); i++){
            out<<setw(15)<<bunnies[normalBunnies[ids[i]]].name<<" was radiated and mutated into vampire!\n";
            bunnies[normalBunnies[ids[i]]].radioactive_mutant_vampire_bunny = true;
            bunnies[normalBunnies[ids[i]]].name="Darth " + bunnies[normalBunnies[ids[i]]].name;
        }
        delete ids;
    }
    out<<"There are now "<<darthPool<<" mutated bunnies!\n";
        //normalBunnies cleared every turn, no need to clear it here
}
void oldDie(vector<Bunny> &bunnies, ostream &out, Bunny &newborn){
    for(vector<Bunny>::iterator i=bunnies.end()-1; i!=bunnies.begin()-1; i--){
        if(i->radioactive_mutant_vampire_bunny == false){
            if(i->age > 10){
                out<<setw(15)<< i->name <<" has died!\n";
                bunnies.erase(i);
            }
        }
        else{
            if(i->age > 50){
                out<<setw(15)<< i->name <<" has died!\n";
                bunnies.erase(i);
            }
        }
    }
}
void newBorn(vector<Bunny> &bunnies, vector<colors> &mothercolors, unsigned short &males, unsigned short &females, ostream &out, Bunny &newborn){
    if(males>0 && females>0){
        out<<"Population's increasing...\n";
        for(unsigned int i=0; i<females; i++){
            newborn = Bunny( mothercolors[i] );
            bunnies.push_back( newborn );
            out<<setw(15)<<bunnies.at(bunnies.size()-1).name<<" was born! There are now "<<bunnies.size()<<" bunnies! "<< bunnies.size()<<"\n";
        }
    }
}
void killHalf(vector<Bunny> &bunnies, ostream &out, Bunny &newborn){
    int* ids= new int[bunnies.size()];
    FYShuffle(bunnies.size(), ids);
    for(unsigned int i=0; i<bunnies.size()/2 ;i++){
        bunnies.erase(bunnies.begin()+ids[i]);
    }
    delete ids;
    out<<setw(4)<<bunnies.size()<<" bunnies left.\n";
}
void overPop(vector<Bunny> &bunnies, ostream &out, Bunny &newborn){
    if(bunnies.size() > 1000){
        out<<"FOOD SHORTAGE OVER 1000 BUNNIES\n";
        killHalf(bunnies, out, newborn);
    }
}

void printBoard(vector<Bunny> &bunnies){

}

int main(){
    fstream out;

    vector <Bunny> bunnies;
    vector <colors> mothercolors;
    vector <int> normalBunnies;

    unsigned short males, females;

    srand(time(NULL));
    if(Bunny::getNames("MaleBunnies.txt", 1) || Bunny::getNames("FemaleBunnies.txt", 0)){
        cout<<"Couldn't get access to bunny names file! The program will now close."<<endl;
        return 1;
    }
//
//    out.open("abcd.txt", ios::trunc|ios::out); //file for output
//    if(!out.is_open()){
//        cout<<"Couldn't open output file \"abcd.txt\"";
//        return 2;
//    }

    Bunny newborn = Bunny( static_cast<colors>( rand()%4) );  //bufferbunny
    for(unsigned int i =0; i < 5; i++){
        newborn = Bunny( static_cast<colors>( rand()%4), rand()%80, rand()%80 );
        bunnies.push_back( newborn );
        out<<setw(15)<<bunnies.at(bunnies.size()-1).name<<" was born! There are now "<<setw(4)<<bunnies.size()<<" bunnies!\n";
    }

    while(bunnies.size() != 0){ //main loop
        std::this_thread::sleep_for(std::chrono::milliseconds((long long)(fmod(abs(10-((double)clock()/CLOCKS_PER_SEC)), 2.0) * 1000)));

        if(GetKeyState('k') || GetKeyState('K') || GetKeyState(VK_NUMPAD0)){
                killHalf(bunnies, out, newborn);
        }

        males = 0;
        females = 0;
        normalBunnies.clear();
        mothercolors.clear();

        //_________________________________PRINT BUNNY TABLE_________________________________________________________________
        printBunnyTable(bunnies, males, females, normalBunnies, mothercolors, out, newborn);
        //_________________________________VAMPIRE SPREAD_________________________________________________________________
        vampireSpread(bunnies, normalBunnies, out, newborn);
        //_________________________________OLD BUNNIES DIE_________________________________________________________________
        oldDie(bunnies, out, newborn);
        //_________________________________NEW BUNNIES BORN_________________________________________________________________
        newBorn(bunnies, mothercolors, males, females, out, newborn);
        //_________________________________OVERPOPULATION_________________________________________________________________
        overPop(bunnies, out, newborn);
        //_________________________________PRINT BOARD_________________________________________________________________
        printBoard(bunnies);

    }
    return 0;
}


