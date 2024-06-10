#include <iostream>
#include "MasterMindSolution/MasterMind_BF.h"

int main() {
    MasterMind_BF masterMind({4,"../data/color.txt",true});

    std::cout<<masterMind.getGuessSolution();
    std::cout<<masterMind.goal();
    return 0;
}
