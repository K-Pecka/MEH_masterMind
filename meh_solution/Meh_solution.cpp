#include "Meh_solution.h"

int Meh_solution::randomInt(int min,int max){
    using namespace std;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}