
#ifndef BUNNY_H
#define BUNNY_H

enum colors
{
    white,
    brown,
    black,
    spotted
};

class Bunny
{
    public:
        static std::vector <std::string> maleNames;
        static std::vector <std::string> femaleNames;
        static bool getNames(std::string fileName, bool mf);
		static int board[80][80];

        Bunny(colors mothercolor);

        unsigned short x, y;

        bool sex, radioactive_mutant_vampire_bunny;
        colors color;
        unsigned short age;
        std::string name;
    protected:

    private:
};

#endif // BUNNY_H
