#include "MasterMind.h"

std::ostream& operator<<(std::ostream& o, const color_t& g){
    for (int i = 0; i < g.size(); i++) {
        o << g[i]<<" ";
    }
    o<<std::endl;
    return o;
}
void MasterMind::generateRandomSolution()
{
    solution.clear();
    for (int i = 0; i < lengthSolution; ++i) {
        solution.push_back(possibleColors.colors[randomInt(0,(int)possibleColors.colors.size()-1)]);
    }
}
void MasterMind::init() {
    generateRandomSolution();
}
int MasterMind::getRandomPosition() {
    return randomInt(0, lengthSolution);
}
bool MasterMind::loadGuessesFromFile(const std::string& filename) {
        std::ifstream file(filename);

        possibleColors.colors.clear();

        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file " << filename << std::endl;
            return false;
        }
        std::string temp;
        while (file >> temp) {
            possibleColors.colors.push_back(temp);
        }
        file.close();
        return true;
}