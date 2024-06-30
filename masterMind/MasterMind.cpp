#include "MasterMind.h"

std::ostream& operator<<(std::ostream& o, const solution_t& g) {
    for (const auto& color : g) {
        o << color << " ";
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
    return randomInt(0, config.colorLength);
}
void MasterMind::init() {
    try {
        guessSolution =setLoadSolution(config.pathSolutionFile);
        theBestSolution = solution_t (config.codeLength);
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        exit(-1);
    }
}

solution_t MasterMind::generateRandomSolution() {
    solution_t randomSolution;
    for (int i = 0; i < config.codeLength; ++i) {
        randomSolution.push_back(randomColor());
    }
    if (randomSolution.empty() || config.codeLength == 0) {
        throw std::runtime_error("Error: solution is empty or code length = 0");
    }
    return randomSolution;
}
Solutions MasterMind::setLoadSolution(const std::string& path){
    auto loadSolution = loadFile(path);
    config.codeLength = (int)loadSolution[0].first.size();
    return loadSolution;
}
Solutions MasterMind::loadFile(const std::string& path) const {
    std::ifstream file(path);

    if (!file.is_open()) {
        throw std::runtime_error("Error: Unable to open file " + path);
    }

    Solutions content;
    std::string line1, line2;

    while (std::getline(file, line1) && std::getline(file, line2)) {
        std::istringstream iss1(line1);
        std::istringstream iss2(line2);

        solution_t temp1, temp2;
        int number;

        while (iss1 >> number) {
            temp1.push_back(number);
        }
        if (iss1.fail() && !iss1.eof()) {
            throw std::runtime_error("Error: Invalid integer value in line: " + line1);
        }

        while (iss2 >> number) {
            temp2.push_back(number);
        }
        if (iss2.fail() && !iss2.eof()) {
            throw std::runtime_error("Error: Invalid integer value in line: " + line2);
        }

        content.emplace_back(std::make_pair(temp1, temp2));
    }

    file.close();

    if (file.bad()) {
        throw std::runtime_error("Error: Failed to read the file " + path);
    }

    return content;
}

bool MasterMind::betterSolution(const solution_t &guess) {
    if(config.communication)std::cout << goal(guess) << ">" << goal(theBestSolution) << std::endl;
    auto guessGoal = goal(guess);
    auto theBestSolutionGoal = goal(theBestSolution);
    if (guessGoal > theBestSolutionGoal) {
        setSolution(guess);
        return true;
    }
    return false;
}

int MasterMind::goal(const solution_t& guess) {
    int totalCorrect = 0;

    for (size_t i = 0; i < guessSolution.size(); ++i) {
         auto solution = guessSolution[i];
         auto sum = 0;
        for(size_t j = 0; j < solution.first.size(); ++j)
        {
            if(guess[i] == solution.first[j]){
                sum+=solution.second[j];
            }
        }
        totalCorrect+=sum;
    }
    return totalCorrect;
}

std::vector<solution_t> MasterMind::generateNeighbor() {
    std::vector<solution_t> result;
    for (size_t i = 0; i < theBestSolution.size(); ++i) {
            solution_t modified = getTheBestSolution();
            modified[i] = randomColor();
            result.push_back(modified);
    }
    return result;
}

std::vector<solution_t> MasterMind::generateNeighbor(const solution_t &currentSolution) {
    std::vector<solution_t> result;
    for (size_t i = 0; i < currentSolution.size(); ++i) {
        solution_t modified = currentSolution;
            modified[i] = randomColor();
            result.push_back(modified);
    }
    return result;
}

solution_t MasterMind::theBestNeighbor(std::vector<solution_t>& neighbors)
{
    if (neighbors.empty()) {
        throw std::invalid_argument("neighbor list is empty");
    }
    auto it = *std::max_element(neighbors.begin(), neighbors.end(), [this](auto a, auto b) {
            return goal(a) > goal(b);
    });

    return it;
}
solution_t MasterMind::randomNeighbor(std::vector<solution_t> & neighbors) {
    if (neighbors.empty()) {
        throw std::invalid_argument("neighbor list is empty");
    }
    return neighbors[randomInt(0,(int)neighbors.size()-1)];
}


solution_t MasterMind::getTheBestSolution() {
    solution_t solutionL;
   for(const auto& solutionColor: theBestSolution)
   {
       solutionL.push_back(solutionColor);
   }
    return solutionL;
}

void MasterMind::printSolve() {
    auto start_time = std::chrono::system_clock::now();
    std::cout << solve();

    std::cout<<goal(theBestSolution);
    std::cout<<std::endl;

    auto end_time = std::chrono::system_clock::now();
    auto computation_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    if(!config.testMode)std::cout<< computation_time.count()<< " microseconds" << std::endl;
    else std::cout << computation_time.count()<< std::endl;
}

void MasterMind::setSolution(solution_t guess) {
    theBestSolution = guess;
}
bool MasterMind::isInParams(Param p)
{
    return std::find(config.params.begin(), config.params.end(), p) != config.params.end();
}
bool MasterMind::fullCompatibility(solution_t guess){
    return goal(guess) == config.codeLength*2;
}