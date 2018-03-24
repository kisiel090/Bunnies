#include<iostream>
#include<time.h>
#include<cstdlib>
#include<vector>
#include<iomanip>
#include<fstream>

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

int main(){
    if(Bunny::getNames("MaleBunnies.txt", 1) || Bunny::getNames("FemaleBunnies.txt", 0)){
        cout<<"Couldn't get access to bunny names file! The program will now close."<<endl;
        return 1;
    }

    vector <Bunny> bunnies;
    srand(time(NULL));
    vector <colors> mothercolors;
    vector <int> normalBunnies;
    unsigned short males, females;



    Bunny newborn = Bunny( static_cast<colors>( rand()%4) );
    bunnies.push_back( newborn );
    cout<<bunnies.at(bunnies.size()-1).name<<" was born! There are now "<<Bunny::cnt<<" bunnies!"<<endl;
    for(int i =0; i < 10; i++){
        newborn = Bunny( static_cast<colors>( rand()%4) );
        bunnies.push_back( newborn );
        cout<<bunnies.at(bunnies.size()-1).name<<" was born! There are now "<<Bunny::cnt<<" bunnies!"<<endl;
    }

    while(bunnies.size() != 0){
        males = 0;
        females = 0;
        normalBunnies.clear();
        mothercolors.clear();
        cout<<bunnies.size()<<endl;
        cout<<"|age| name            |S|C|V |"<<endl;
        cout<<"------------------------------"<<endl;
        for(int i=0; i<bunnies.size(); i++){
            // |  9|fjbaf sadfasdf   |1|2|0 |
            cout<<"||"<<setw(2)<<bunnies[i].age<<"|"<<setw(17)<<bunnies[i].name<<"|"<<setw(1)<<bunnies[i].sex<<"|"<<setw(1)<<bunnies[i].color<<"|"<<setw(1)<<bunnies[i].radioactive_mutant_vampire_bunny<<"||"<<endl;

            bunnies[i].age++;
            if(bunnies[i].radioactive_mutant_vampire_bunny == false){
                normalBunnies.push_back(i); //needed later for vampires spread
                if(bunnies[i].age>2){
                    if(bunnies[i].sex){
                        cout<<bunnies[i].name<<" is a capable male!"<<endl;
                        males++;
                    }
                    else{
                        cout<<bunnies[i].name<<" is a capable female!"<<endl;
                        females++;
                        mothercolors.push_back( bunnies[i].color); //childrens are born with mother color
                    }
                }
            }
        }
        cout<<"------------------------------"<<endl;

        int darthPool = bunnies.size()-normalBunnies.size();
        cout<<"There are now "<<darthPool<<" mutated bunnies!"<<endl;
        if(darthPool!=0){
            int* ids= new int[normalBunnies.size()];
            FYShuffle(normalBunnies.size(), ids);
            cout<<"Radioactive mutant vampire bunnies are spreading..."<<endl;
            for(int i = 0; i<darthPool || i<normalBunnies.size(); i++){
                cout<<bunnies[normalBunnies[ids[i]]].name<<" was radiated and mutated into vampire!"<<endl;
                bunnies[normalBunnies[ids[i]]].radioactive_mutant_vampire_bunny = true;
                bunnies[normalBunnies[ids[i]]].name="Darth " + bunnies[normalBunnies[ids[i]]].name;
            }
            delete ids;
        }
            //normalBunnies cleared every turn, no need to clear it here



        for(int i=0; i<bunnies.size(); i++){
            if(bunnies[i].radioactive_mutant_vampire_bunny == false){
                if(bunnies[i].age > 10){
                    cout<<bunnies[i].name<<" has died!"<<endl;
                    bunnies.erase(bunnies.begin()+i);
                }
            }
            else{
                if(bunnies[i].age > 50){
                    cout<<bunnies[i].name<<" has died!"<<endl;
                    bunnies.erase(bunnies.begin()+i);
                }
            }
        }


        if(males>0 && females>0){
            cout<<"Population's increasing..."<<endl;
            for(int i=0; i<females; i++){
                newborn = Bunny( mothercolors[i] );
                bunnies.push_back( newborn );
                cout<<bunnies.at(bunnies.size()-1).name<<"was born! There are now "<<Bunny::cnt<<" bunnies! "<< bunnies.size()<<endl;
            }
        }
        if(bunnies.size() > 1000){
            cout<<"FOOD SHORTAGE OVER 1000 BUNNIES"<<endl;
            int* ids= new int[bunnies.size()];
            FYShuffle(normalBunnies.size(), ids);
            for(int i=0; i<bunnies.size()/2 ;i++){
                bunnies.erase(bunnies.begin()+ids[i]);
            }
            delete ids;
            cout<<Bunny::cnt<<" bunnies left."<<endl;
        }
    }
    system("PAUSE");
    return 0;
}


