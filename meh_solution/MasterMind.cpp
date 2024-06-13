#include "MasterMind.h"

int MasterMind::randomInt(int min, int max){
    using namespace std;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}
std::ostream& operator<<(std::ostream& o, const color_t& g) {
    for (const auto& color : g) {
        o << color << " ";
    }
    o << std::endl;
    return o;
}
std::ostream& operator<<(std::ostream& o, const std::vector<std::pair<std::string, bool>>& g) {
    for (const auto& pair : g) {
        o <<"{"<< pair.first << ","<<pair.second<<"}";
    }
    o << std::endl;
    return o;
}
std::ostream& operator<<(std::ostream& o, const std::vector<bool>& result) {
    for(bool position : result) {
        o << (position ? "1" : "0")<<" ";
    }
    o << std::endl;
    return o;
}
void MasterMind::init() {
    try {
        loadGuessesFromFile();
        correctSolution = generateRandomSolution();
        solution = std::vector<std::pair<std::string, bool>>(config.codeLength, {"", false});
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        exit(-1);
    }
}
color_t MasterMind::getGuessSolution() {
    if(config.communication)std::cout << "Solution: ";
    return correctSolution;
}
void MasterMind::loadGuessesFromFile() {
    std::ifstream file(config.pathColorFile);

    possibleColors.colors.clear();

    if (!file.is_open()) {
        throw std::runtime_error("Error: Unable to open file " + config.pathColorFile);
    }
    std::string temp;
    while (file >> temp) {
        possibleColors.colors.push_back(temp);
    }
    file.close();
}
int MasterMind::randomColor() const
{
    return randomInt(0, (int)possibleColors.colors.size() - 1);
}
color_t MasterMind::generateRandomSolution() {
    color_t randomSolution;
    for (int i = 0; i < config.codeLength; ++i) {
        randomSolution.push_back(possibleColors.colors[randomColor()]);
    }
    if (randomSolution.empty() || config.codeLength == 0) {
        throw std::runtime_error("Error: solution is empty or code length = 0");
    }
    return randomSolution;
}
bool MasterMind::betterSolution(const color_t &guess) {
   // std::cout<<getCorrectPosition(guess,correctSolution);
    if (checkColor(guess) > checkColor(solution)) {
        setSolution(guess);
        return checkColor(solution) == config.codeLength;
    }
    return false;
}
int MasterMind::checkColor(const color_t& guess) {
    int correctColors = 0;
    for (size_t i = 0; i < guess.size(); ++i) {
        if (guess[i] == correctSolution[i]) {
            correctColors++;
        }
    }
    return correctColors;
}

int MasterMind::checkColor(std::vector<std::pair<std::string, bool>>& solution) {
    int correctColors = 0;
    for (auto & pair : solution) {
        if (pair.second) {
            correctColors++;
        }
    }
    return correctColors;
}
color_t MasterMind::generateNeighbor(const color_t &currentSolution) {
    color_t newSolution = currentSolution;
    for (size_t i = 0; i < newSolution.size(); ++i) {
        if (!solution[i].second) {
            newSolution[i] = possibleColors.colors[randomColor()];
        }
    }
    return newSolution;
}

std::vector<bool> MasterMind::getCorrectPosition(color_t colorCorrect, color_t colorGuess) {
    std::vector<bool> correct(config.codeLength, false);
    for (size_t i = 0; i < colorCorrect.size(); ++i) {
        correct[i] = (colorCorrect[i] == colorGuess[i]);
    }
    return correct;
}

void MasterMind::showCorrectPosition(std::vector<bool> positions) {
    float count=0;
    for(bool position : positions) {
        if(position)count++;
    }
    std::cout<<positions;
    std::cout<<count<<"/"<<config.codeLength<<std::endl;
    std::cout<<(count/config.codeLength)*100<<"%"<<std::endl;
}

color_t MasterMind::getSolution() {
   color_t solutionL;
   for(const auto& solutionColor: solution)
   {
       solutionL.push_back(solutionColor.first);
   }
    return solutionL;
}
void MasterMind::printSolve() {
    if(config.communication) std::cout << "Correct solution: ";
    std::cout<<correctSolution;
    goal();
    std::cout<<getSolution();
    if(config.communication)showCorrectPosition(getCorrectPosition( correctSolution,getSolution()));
    std::cout<<getCorrectPosition( correctSolution,getSolution());
}

void MasterMind::setSolution(color_t guess) {
    for (size_t i = 0; i < guess.size(); ++i) {
        solution[i] = {guess[i], guess[i] == correctSolution[i]};
    }
}