#include "MasterMind.h"

std::ostream& operator<<(std::ostream& o, const color_t& g) {
    for (const auto& color : g) {
        o << color << " ";
    }
    o << std::endl;
    return o;
}
std::ostream& operator<<(std::ostream& o, const vector& g) {
    for (const auto& pair : g) {
        o <<"{"<< pair.first << ","<<pair.second<<"}";
    }
    o << std::endl;
    return o;
}
std::ostream& operator<<(std::ostream& o, const std::vector<tinyInt>& result) {
    for(tinyInt position : result) {
        o << position<<" ";
    }
    o << std::endl;
    return o;
}

std::mt19937 MasterMind::random() {
    std::random_device rd;
    std::mt19937 random(rd());
    return random;
}
int MasterMind::randomInt(int min, int max){
    using namespace std;
    auto gen = random();
    uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}
double MasterMind::randomFloat(double min, double max){
    using namespace std;
    auto gen = random();
    uniform_real_distribution<double> dis(min, max);
    return dis(gen);
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

void MasterMind::init() {
    try {
        possibleColors.colors=loadFile(config.pathColorFile);
        correctSolution =(!config.pathSolutionFile.empty())?setLoadSolution(config.pathSolutionFile):generateRandomSolution();
        theBestSolution = vector(config.codeLength, {"", 0});
        colorInSolution = isInSolution(correctSolution);
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        exit(-1);
    }
}

color_t MasterMind::getGuessSolution() {
    if(config.communication)std::cout << "Solution: ";
    return correctSolution;
}
color_t MasterMind::setLoadSolution(const std::string& path){
    auto loadSolution = loadFile(path);
    config.codeLength = (int)loadSolution.size();
    return loadFile(path);
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
int MasterMind::getCorrectCounter(const color_t& solution){
    int counter = 0;
    for(int i=0;i<solution.size();i++) counter += (solution[i]==correctSolution[i]) ?1:0;
    return counter;
}
bool MasterMind::betterSolutionAbsolute(const color_t& guess,const color_t& current){
    return getCorrectCounter(guess) > getCorrectCounter(current);
}

bool MasterMind::betterSolution(const color_t &guess) {
    if(config.communication)std::cout << goal(guess) << ">" << goal(theBestSolution) << std::endl;
    auto guessGoal = goal(guess);
    auto theBestSolutionGoal = goal(theBestSolution);
    if (guessGoal >= theBestSolutionGoal) {
        if(guessGoal == theBestSolutionGoal)
        {
            if(betterSolutionAbsolute(guess,getTheBestSolution()))setSolution(guess);
            return true;
        }
        setSolution(guess);
        return true;
    }
    return false;
}
int MasterMind::goal(const color_t& guess) {
    int correctColors = 0;
    for (size_t i = 0; i < guess.size(); ++i) {
        if(colorInSolution.find(guess[i]) != colorInSolution.end())
        {
            correctColors++;
        }
        if (guess[i] == correctSolution[i]) {
            correctColors++;
        }
    }
    return correctColors;
}

int MasterMind::goal(vector& solution) {
    int correctColors = 0;
    for (auto & pair : solution) {
        if (pair.second) {
            correctColors+=pair.second;
        }
    }
    return correctColors;
}
std::vector<color_t> MasterMind::generateNeighbor() {
    std::vector<color_t> result;
    for (size_t i = 0; i < theBestSolution.size(); ++i) {

            color_t modified = getTheBestSolution();
            modified[i] = possibleColors.colors[randomColor()];
            result.push_back(modified);

    }
    return result;
}
std::vector<color_t> MasterMind::generateNeighbor(const color_t &currentSolution) {
    std::vector<color_t> result;
    for (size_t i = 0; i < currentSolution.size(); ++i) {
            color_t modified = currentSolution;
            modified[i] = possibleColors.colors[randomColor()];
            result.push_back(modified);
    }
    return result;
}

color_t MasterMind::theBestNeighbor(std::vector<color_t>& neighbors)
{
    if (neighbors.empty()) {
        throw std::invalid_argument("neighbor list is empty");
    }
    auto it = *std::max_element(neighbors.begin(), neighbors.end(), [this](auto a, auto b) {
        if (goal(a) == goal(a)) {
            return betterSolutionAbsolute(a, b);
        } else {
            return goal(a) > goal(b);
        }
    });

    return it;
}
color_t MasterMind::randomNeighbor(std::vector<color_t> & neighbors) {
    if (neighbors.empty()) {
        throw std::invalid_argument("neighbor list is empty");
    }
    return neighbors[randomInt(0,(int)neighbors.size()-1)];
}
std::vector<tinyInt> MasterMind::getCorrectPosition(color_t colorCorrect, color_t colorGuess) const {
    std::vector<tinyInt> correct(config.codeLength, 0);
    auto color = isInSolution(colorCorrect);
    for (size_t i = 0; i < colorGuess.size(); ++i) {
        tinyInt correctPosition = 0;
        if(color.find(colorGuess[i]) != color.end())correctPosition++;
        if (colorCorrect[i] == colorGuess[i]) correctPosition++;
        correct[i]=correctPosition;
    }
    return correct;
}

void MasterMind::showCorrectPosition(const std::vector<tinyInt>& positions) const {
    auto max = config.codeLength * weight;
    auto count=std::accumulate(positions.begin(), positions.end(), 0.0);
    std::cout<<positions;
    std::cout<<count<<"/"<<max<<std::endl;
    std::cout<<(count/max)*100<<"%"<<std::endl;
}

color_t MasterMind::getTheBestSolution() {
   color_t solutionL;
   for(const auto& solutionColor: theBestSolution)
   {
       solutionL.push_back(solutionColor.first);
   }
    return solutionL;
}
void MasterMind::printSolve() {
    if(config.communication) std::cout << "Correct solution: ";
    std::cout<<correctSolution;
    auto start_time = std::chrono::system_clock::now();
    solve();
    auto end_time = std::chrono::system_clock::now();
    auto computation_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    std::cout << getTheBestSolution();
    showCorrectPosition(getCorrectPosition(correctSolution, getTheBestSolution()));
    std::cout << computation_time.count() << " microseconds" << std::endl;

}

void MasterMind::setSolution(color_t guess) {
    auto color = isInSolution(guess);
    for (size_t i = 0; i < guess.size(); ++i) {
        auto correctColors = 0;
        if(color.find(guess[i]) != color.end())
        {
            correctColors++;
        }
        if (guess[i] == correctSolution[i]) {
            correctColors++;
        }
        theBestSolution[i] = {guess[i], correctColors};
    }
}
bool MasterMind::isInParams(Param p)
{
    return std::find(config.params.begin(), config.params.end(), p) != config.params.end();
}

bool MasterMind::fullCompatibility(color_t& correct) {
    return goal(correct) == config.codeLength * weight;
}

std::set<std::string> MasterMind::isInSolution(const color_t& solution) {
    std::set<std::string> result;
    for (const auto& color : solution) {
        result.insert(color);
    }
    return result;
}
