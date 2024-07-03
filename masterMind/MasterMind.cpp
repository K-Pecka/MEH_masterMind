#include "MasterMind.h"

#include <utility>

std::ostream& operator<<(std::ostream& o, const solution_t& g) {
    for (const auto& el : g) {
        o << el << " ";
    }
    o << std::endl;
    return o;
}
std::ostream& operator<<(std::ostream& o, const std::unordered_map<int,int>& g) {
    o<<"{";
    for (const auto& el : g) {
        o << el.first << " : "<< el.second<<" ";
    }
    o <<"}"<< std::endl;
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

solution_t MasterMind::generateRandomSolution() const {
    solution_t randomSolution;
    for (int i = 0; i < config.codeLength; ++i) {
        randomSolution.push_back(randomColor());
    }
    if (randomSolution.empty() || config.codeLength == 0) {
        throw std::runtime_error("Error: solution is empty or code length = 0");
    }
    return randomSolution;
}
solutions MasterMind::setLoadSolution(const std::string& path){
    auto loadSolution = loadFile(path);
    config.codeLength = (int)loadSolution[0].first.size();
    return loadSolution;
}
solutions MasterMind::loadFile(const std::string& path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        throw std::runtime_error("Error: Unable to open file " + path);
    }

    solutions content;
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
        auto max = std::max_element(temp1.begin(), temp1.end());
        if(max != temp1.end())  config.colorLength = std::max(*max,config.colorLength);
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
std::unordered_map<int,int> mapGuessSolution( const solution_t& guess)
{
    std::unordered_map<int,int> solutionMap;
    for(auto e:guess)solutionMap[e]++;
    return solutionMap;
}
int getGoalValue(const solution_t& score, const solution_t& value) {
    int result = 0;
    auto map = mapGuessSolution(score);
    for (int i=0;i<2;i++) {
        result += (map[i+1] - value[i] )*(i+1);
    }
    return result;
}
solution_t isInSolution(std::unordered_map<int, int>& SolutionMap,solution_t solution,solution_t guess)
{
    solution_t result(solution.size(),0);
    for(int i=0;i<solution.size();i++)
    {
        if(solution[i] == guess[i])
        {
            SolutionMap[guess[i]]--;
            result[i] = 2;
        }
    }
    return result;
}
int MasterMind::goal(const solution_t& guess) {
    lastScore.clear();
    //std::cout<<"->GOOL GUESS: "<<guess;
    int totalCorrect = 0;
    auto solutionMap = mapGuessSolution(guess);
    for (auto solution: guessSolution) {
        //std::cout<<"->solution: "<<solution.first;
        auto solutionMapCopy = solutionMap;
        solution_t score(config.codeLength,0);
        score = isInSolution(solutionMapCopy,solution.first,guess);
        for(int i=0;i<solution.first.size();i++){
           //std::cout<<solutionMapCopy;
           if(score[i]==2)continue;
           if(solutionMapCopy.count(solution.first[i]) <0 || solutionMapCopy[solution.first[i]] == 0)score[i] = 0;
           else{
               solutionMapCopy[solution.first[i]]--;
               score[i]++;
           }
       }
        auto v = getGoalValue(score,solution.second);
        lastScore.emplace_back(score,v);
       totalCorrect+=v;
       //std::cout<<"->score"<<score<<std::endl;
       //std::cout<<std::endl;

    }
   // std::cout<<"<-GOOL"<<std::endl;
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

std::vector<solution_t> MasterMind::generateNeighbor(const solution_t &currentSolution) const {
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
    return theBestSolution;
}

void MasterMind::printSolve() {

    auto start_time = std::chrono::system_clock::now();
    std::cout << solve();
    std::cout<<"======SOLVE=========="<<std::endl;
    std::cout<<goal(theBestSolution);
    if(config.communication)
        for(const auto& e:lastScore)std::cout<<std::endl<<"score->"<<std::endl<<e.first<<"goal: "<<e.second<<std::endl<<"<-";
    auto end_time = std::chrono::system_clock::now();
    auto computation_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout<<std::endl;
    if(!config.testMode)std::cout<< computation_time.count()<< " ms" << std::endl;
    else std::cout<<computation_time.count()<<std::endl;
    std::cout<<"====================="<<std::endl;
}

void MasterMind::setSolution(solution_t guess) {
    theBestSolution = std::move(guess);
}
bool MasterMind::isInParams(Param p)
{
    return std::find(config.params.begin(), config.params.end(), p) != config.params.end();
}
bool MasterMind::fullCompatibility(const solution_t& guess){
    goal(guess);
    for(auto& e:lastScore)
    {
        auto map =  mapGuessSolution(e.first);
        if(map[2] == config.codeLength)return true;
    }
    return false;
}