#include "MasterMind.h"

std::ostream& operator<<(std::ostream& o, const color_t& g) {
    for (const auto& color : g) {
        o << color << " ";
    }
    o << std::endl;
    return o;
}

void MasterMind::init() {
    try {
        loadGuessesFromFile();
        generateRandomSolution();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        exit(-1);
    }
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

void MasterMind::generateRandomSolution() {
    solution.clear();
    for (int i = 0; i < config.codeLength; ++i) {
        solution.push_back(possibleColors.colors[randomInt(0, (int)possibleColors.colors.size() - 1)]);
    }
    if (solution.empty() || config.codeLength == 0) {
        throw std::runtime_error("Error: solution is empty or code length = 0");
    }
}



bool MasterMind::isCorrectGuess(const color_t& guess) {
    return guess == solution;
}

void MasterMind::generateAllCombinations(int codeLength, std::vector<color_t>& combinations, color_t& currentCombination) {
    if (currentCombination.size() == codeLength) {
        combinations.push_back(currentCombination);
        return;
    }
    for (const auto& color : possibleColors.colors) {
        currentCombination.push_back(color);
        generateAllCombinations(codeLength, combinations, currentCombination);
        currentCombination.pop_back();
    }
}

void MasterMind::bruteForceSolution() {
    std::vector<color_t> combinations;
    color_t currentCombination;
    generateAllCombinations(config.codeLength, combinations, currentCombination);

    for (const auto& combination : combinations) {
        if (isCorrectGuess(combination)) {
            std::cout << "Solution found (BF): " << combination;
            return;
        }
    }
}
