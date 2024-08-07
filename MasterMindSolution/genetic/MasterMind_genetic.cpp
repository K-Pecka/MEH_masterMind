#include "MasterMind_genetic.h"

auto MasterMind_genetic::crossoverFunction(){
    return [&](const solution_t& p1, const solution_t& p2) ->std::vector<solution_t> {
        if (isInParams(Param::DOUBLE_POINT)) {
            return crossoverDoublePoint(p1, p2);
        } else {
            return crossoverSinglePoint(p1, p2);
        }
    };
}
auto MasterMind_genetic::mutateFunction(){
    return [&](std::vector<solution_t>& newPopulation) -> std::vector<solution_t> {
        if (isInParams(Param::SWAP)) {
            return mutateSwap(newPopulation);
        } else {
            return mutateRandom(newPopulation);
        }
    };
}
auto MasterMind_genetic::terminationConditionFunction(){
    return [&]() -> bool {
        if (isInParams(Param::FITNESS)) {
            return terminationConditionFitness();
        } else {
            return terminationConditionGenerations();
        }
    };
}

solution_t MasterMind_genetic::solve() {
    int populationSize = config.GAConfig.population;
    int eliteSize = config.GAConfig.eliteSize;

    auto crossover = crossoverFunction();
    auto mutate = mutateFunction();
    auto terminationCondition = terminationConditionFunction();

    if(populationSize<eliteSize)eliteSize=0;
    population = initializePopulation(populationSize);
    population = selectWithOutElites(eliteSize);

    generation = 0;
    while (!terminationCondition()) {
        population = selectWithOutElites(eliteSize);
        std::vector<solution_t> offspring = crossoverParents(selectParent(fitnesses()), crossover);
        population = mutate(offspring);
        generation++;
    }
    betterSolution(theBestNeighbor(elites));
    betterSolution(theBestNeighbor(population));
    return getTheBestSolution();
}

std::vector<solution_t> MasterMind_genetic::initializePopulation(int populationSize) {
    for (int i = 0; i < populationSize; ++i) population.push_back(generateRandomSolution());
    return population;
}

std::vector<int> MasterMind_genetic::fitnesses() {
    std::vector < int > fit;
    for (auto & e: population) fit.push_back(goal(e));
    return fit;
}

std::vector<int> MasterMind_genetic::selectParent(const std::vector<int>& fit) {
    std::vector < int > result;
    for (int i = 0; i < fit.size(); i++) {
        int idx1 = randomInt(0,(int)fit.size() -1);
        int idx2 = randomInt(0,(int)fit.size() -1);
        if (fit.at(idx1) > fit.at(idx2)) result.push_back(idx1);
        else result.push_back(idx2);
    }
    return result;
}

std::vector<solution_t> MasterMind_genetic::crossoverSinglePoint(const solution_t& parent1, const solution_t& parent2) {
    std::vector<solution_t> children(2, solution_t(config.codeLength));
    int crossoverPoint = randomInt(0, config.codeLength - 1);

    for (int i = 0; i < config.codeLength; ++i) {
        if (i < crossoverPoint) {
            children[0][i] = parent1[i];
            children[1][i] = parent2[i];
        } else {
            children[0][i] = parent2[i];
            children[1][i] = parent1[i];
        }
    }

    return children;
}

std::vector<solution_t> MasterMind_genetic::crossoverDoublePoint(const solution_t& parent1, const solution_t& parent2) {
    std::vector<solution_t> children(2, solution_t(config.codeLength));

    int crossoverPoint1 = randomInt(0, config.codeLength - 1);
    int crossoverPoint2 = randomInt(0, config.codeLength - 1);

    if (crossoverPoint1 > crossoverPoint2) {
        std::swap(crossoverPoint1, crossoverPoint2);
    }

    for (int i = 0; i < config.codeLength; ++i) {
        if (i < crossoverPoint1 || i > crossoverPoint2) {
            children[0][i] = parent1[i];
            children[1][i] = parent2[i];
        } else {
            children[0][i] = parent2[i];
            children[1][i] = parent1[i];
        }
    }

    return children;
}

std::vector<solution_t> MasterMind_genetic::mutateSwap(std::vector<solution_t>& newPopulation) {
    for(auto &m:newPopulation)
    {
        for(auto &_:m)
        {
            if (randomFloat(0.0, 1.0) > config.GAConfig.mutationProb)continue;
            int index1 = randomInt(0, config.codeLength - 1);
            int index2 = randomInt(0, config.codeLength - 1);
            std::swap(m[index1], m[index2]);
        }
    }
    return newPopulation;

}

std::vector<solution_t> MasterMind_genetic::mutateRandom(std::vector<solution_t>& newPopulation) {
    for(auto &m:newPopulation) {
        for(auto &_:m) {
            if (randomFloat(0.0, 1.0) > config.GAConfig.mutationProb)continue;
            int index = randomInt(0, config.codeLength - 1);
            m[index] = randomColor();
        }
    }
    return newPopulation;
}

bool MasterMind_genetic::terminationConditionGenerations() {
        return generation >= config.GAConfig.generation;
}

bool MasterMind_genetic::terminationConditionFitness() {
    auto best = getTheBestSolution();
    return fullCompatibility(best);
}

std::vector<solution_t> MasterMind_genetic::selectWithOutElites(int eliteSize) {
    std::vector<solution_t> populationWithoutElite;
    std::vector<solution_t> combinedPopulation = population;
    if(!elites.empty()){
        combinedPopulation.insert(combinedPopulation.end(), elites.begin(), elites.end());
        elites.clear();
    }

    std::sort(combinedPopulation.begin(), combinedPopulation.end(), [this](const solution_t& a, const solution_t& b) {
        return goal(a) > goal(b);
    });
    std::copy(combinedPopulation.begin() + eliteSize, combinedPopulation.end(), std::back_inserter(populationWithoutElite));
    std::copy(combinedPopulation.begin(), combinedPopulation.begin() + eliteSize, std::back_inserter(elites));
    return populationWithoutElite;
}

std::vector<solution_t> MasterMind_genetic::crossoverParents(std::vector<int> parents, auto crossover) {
    std::vector < solution_t > newPopulation;
    auto random = randomFloat(0.0,1.0);
    for (int i = 0; i < population.size(); i += 2) {
        if(population.size()-1 == i) {
            newPopulation.push_back(population[parents[i]]);
            break;
        }
        solution_t parent1 = population[parents[i]];
        solution_t parent2 = population[parents[i + 1]];
        std::vector<solution_t> currentParents={parent1, parent2};
        std::vector < solution_t > children;
        if (random < config.GAConfig.crossoverProb) children = crossover(parent1,parent2);
        else children = currentParents;
        for (auto & o: children) newPopulation.push_back(o);
    }
    return newPopulation;
}

