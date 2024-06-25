#include "MasterMind.h"

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
int MasterMind::randomInt(int min, int max){
    using namespace std;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}
double MasterMind::randomFloat(double min, double max){
    using namespace std;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(min, max);
    return dis(gen);
}
void MasterMind::init() {
    try {
        possibleColors.colors.clear();
        possibleColors.colors=loadFile(config.pathColorFile);
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
color_t MasterMind::loadFile(const std::string& path) const {
    std::ifstream file(path);

    std::vector<std::string> content;

    if (!file.is_open()) {
        throw std::runtime_error("Error: Unable to open file " + config.pathColorFile);
    }
    std::string temp;
    while (file >> temp) {
        content.push_back(temp);
    }
    file.close();
    return content;
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
    if(config.communication)std::cout<<checkColor(guess)<<">"<<checkColor(solution)<<std::endl;
    if (checkColor(guess) > checkColor(solution)) {
        setSolution(guess);
        return true;
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
std::vector<color_t> MasterMind::generateNeighbor() {
    std::vector<color_t> result;
    for (size_t i = 0; i < solution.size(); ++i) {
        if (!solution[i].second) {
            color_t modified = getSolution();
            modified[i] = possibleColors.colors[randomColor()];
            result.push_back(modified);
        }
    }
    return result;
}
color_t MasterMind::theBestNeighbor(std::vector<color_t>& neighbors)
{
    auto it = *std::max_element(neighbors.begin(), neighbors.end(), [this](auto a, auto b) {
        return checkColor(a) < checkColor(b);
    });

    return it;
}
color_t MasterMind::randomNeighbor(std::vector<color_t> & neighbors) {
    if (neighbors.empty()) {
        throw std::invalid_argument("neighbor list is empty");
    }
    return neighbors[randomInt(0,neighbors.size()-1)];
}
std::vector<bool> MasterMind::getCorrectPosition(color_t colorCorrect, color_t colorGuess) const {
    std::vector<bool> correct(config.codeLength, false);
    for (size_t i = 0; i < colorCorrect.size(); ++i) {
        correct[i] = (colorCorrect[i] == colorGuess[i]);
    }
    return correct;
}

void MasterMind::showCorrectPosition(const std::vector<bool>& positions) const {
    float count=0;
    for(bool position : positions) {
        if(position)count++;
    }
    std::cout<<positions;
    std::cout<<count<<"/"<<config.codeLength<<std::endl;
    std::cout<<(count/float(config.codeLength))*100<<"%"<<std::endl;
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
    auto start_time = std::chrono::system_clock::now();
    goal();
    auto end_time = std::chrono::system_clock::now();
    auto computation_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    std::cout<<getSolution();
    showCorrectPosition(getCorrectPosition( correctSolution,getSolution()));
    std::cout << computation_time.count() << " microseconds" << std::endl;

}

void MasterMind::setSolution(color_t guess) {
    for (size_t i = 0; i < guess.size(); ++i) {
        solution[i] = {guess[i], guess[i] == correctSolution[i]};
    }
}
bool MasterMind::isInParams(Param p)
{
    return std::find(config.params.begin(), config.params.end(), p) != config.params.end();
}