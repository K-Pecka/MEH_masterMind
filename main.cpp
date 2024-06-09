#include <iostream>
#include "MasterMind/MasterMind.h"

int main()
{
    MasterMind masterMind(9);
    if(!masterMind.loadGuessesFromFile("../data/color.txt"))return 0;
    masterMind.init();
    std::cout<<masterMind.getGuessSolution()<<std::endl;
}